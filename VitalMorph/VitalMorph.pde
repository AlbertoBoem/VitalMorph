import processing.serial.*;
import java.nio.ByteBuffer;

//Save on a text file
PrintWriter output;
//time stamps
long time_msc; 
int min;
int sec;
long startTime;


// Serial communication
Serial[] serialPort;
static int NODESNUM = 5;    // maximum number of the serial port
static boolean[] NODEENABLE = {
    true,    // VM1 enable
    true,    // VM2 enable
    false,     // VM3 enable
    false,     // VM4 enable
    false,      // VM5 enable
};

// Frequency of input signal
int count = 0;
int DEVIDECOUNT = 1;        // Freqency control (1:Fastest)

// Moving angle
int ANGLE = 30;

// Font
PFont fontLarge;
PFont fontSmall;

// The number of graph which is shown
int graphCount;
int graphHeight;
int expanded;

// for loading the text file
Table table;

// Sampling
int lowestSample;
int highestSample;
int sampleRate = 360;       // sampling rate used for the physiologic data
                            // into the CSV file

// This class is for processing each vital data
class VitalData{
    public String name;     // name of vital sign

    private int val;        // recieved value
    private int[] values;   // values for visualization

    public byte[] tx;       // for serial communication (this is for integer data)
    public byte txb;        // for serial communication (this is for byte data)

    private int currentSample;

    public int max;
    public int min;

    public int red;
    public int green;
    public int blue;

    // constructor
    public VitalData(int r, int g, int b){
        this.values = new int[width];

        this.max = -99999;
        this.min = 99999;

        this.red = r;
        this.green = g;
        this.blue = b;
    }

    // for plotting waveforms
    public int getY(int arg){
        return (int)(this.values[arg] / 1023.0f * height/2) - 1;
    }

    // update the data for dorawing graphs
    public void updateData(){
        //sample from a specific row
        //the variables currentSample... can be transmitted to the serial port
        this.currentSample = this.grabSampleFromTestData();

        //this.storeSampleData();
        this.normalizeSampleData();

        //mapped value for visualization
        float mappedValue = map((float)this.currentSample, lowestSample, highestSample, height/2, 0);

        val = int(mappedValue);

        // these are esentially buffers for incoming data
        int newDataPoint = val;

        for(int i = 0; i < width - 1; i++){
            this.values[i] = this.values[i + 1];
        }

        this.values[width - 1] = newDataPoint;
    }

    // normalize the sample data for sending
    // acceptable data for servo input is from 0 to 180
    private void normalizeSampleData(){
        float current = this.currentSample - this.min;
        float norm = current / (float)(this.max - this.min); 
        //println(norm);

        this.txb = (byte)(norm * ANGLE);

        if(this.txb < 0){
            this.txb = (byte)(-this.txb);
        }
        
        //only milliseconds work
        //current sample + normalized + the adapted one 
        //output.println(time_msc + "\t" + this.currentSample + "\t" + norm + "\t" + this.txb);
        //output.println(startTime + "\t" + "\t" + this.currentSample + "\t" + norm + "\t" + this.txb);
    }

    // store and convert the sample data for sending
    // float data is converted into byte array to send them as ASCII code
    private void storeSampleData() {

        // convert a float data to 4 byte data
        ByteBuffer buffer = ByteBuffer.allocate(4);
        buffer.clear();
        buffer.putInt(this.currentSample);
        byte[] temp = buffer.array();

        // detect 0x10 from byte array (0x10 is the control characer in ASCII code)
        int count = 0;
        for(int i = 0; i < temp.length; i++){
            if(temp[i] == 0x10){
                count++;
            }
        }

        tx = new byte[4 + count + 4];

        int idx = 0;
        tx[idx++] = 0x10;   // control character
        tx[idx++] = 0x02;   // stx character

        // payload
        for(int i = 0; i < temp.length; i++){
            if(temp[i] == 0x10){
                tx[idx++] = 0x10;
            }

            tx[idx++] = temp[i];
        }

        tx[idx++] = 0x10;   // control character
        tx[idx++] = 0x03;   // etx character
    }

    //-----------------------------Grab sample from CSV file------------------
    // function return a float value of the values from a specific row
    private int grabSampleFromTestData(){

        float stepAmount = sampleRate / frameRate;

        int sampleNumber = floor((frameCount*stepAmount)%table.getRowCount());

        return table.getRow(sampleNumber).getInt(this.name);
    }
}

VitalData[] vitalData;

void setup(){
  
    

    size(1000, 700, P2D);
    //fullScreen(P2D);

    // load fonts
    fontLarge = loadFont("TrebuchetMS-20.vlw");
    fontSmall = loadFont("Uni0554-8.vlw");

    vitalData = new VitalData[5];
    vitalData[0] = new VitalData(0, 255, 0);
    vitalData[1] = new VitalData(255, 255, 0);
    vitalData[2] = new VitalData(255, 255, 255);
    vitalData[3] = new VitalData(255, 0, 0);
    vitalData[4] = new VitalData(0, 255, 255);

    //Save in a text file
    output = createWriter("positions.txt");
    //------------------------------------------
    
    serialPort = new Serial[5];
    for(int i = 0; i < NODESNUM; i++){
        if(NODEENABLE[i]){
            String iname = "/dev/tty.VM" + (i + 1) + "-DevB";
            serialPort[i] = new Serial(this, iname, 19200);
        }
    }
//Modify this part
    vitalData[0].name = "'ECG lead V'"; //1) "'ECG lead V'"; 
    vitalData[1].name = "'ART'";        //2) "'ART'"; 
    vitalData[2].name = "'Resp. Imp.'";        //3) "'Resp. Imp.'"; 
    vitalData[3].name = "'PAP'";        //4) "'PAP'";
    vitalData[4].name = "'CVP'";       //5) "'CVP'";

    // load text file
    lowestSample = 99999;
    highestSample = -99999;
    initSampleData("samples_all2.csv"); // file path ./data/

    // Count a number of shown graph
    graphCount = 0;
    for(int i = 0; i < 5; i++){
        if(NODEENABLE[i]){
            graphCount++;
        }
    }

    // Set the graph parameter
    graphHeight = height / graphCount;
    expanded = graphHeight - height / 5;

    frameRate(60);
    smooth();
}

void draw(){

    background(0);
    
    //Save in a text file
    time_msc = millis();
    min = minute();
    sec = second();
    //time_msc /= 1000;
    //-------------------------------
    
    startTime = System.nanoTime();
  
  
    for(int i = 0; i < 5; i++){
        vitalData[i].updateData();
    }

    thread("sendData");

    //
    //----------------Plot waveforms----------------
    //
    int offset = 0;

    for(int i = 0; i < 5; i++){
        pushMatrix();

        // In this version, graph height is automatially changed by node enable flag
        // If some serial port is disabled, corresponding graph will disappear
        // The x-coordinate of top line is 20.
        // The x-coordinate of botom line is 680.
        if(NODEENABLE[i]){
            int xoffset = (i - offset) * graphHeight;

            // Text
            fill(150);
            textFont(fontLarge);
            text(vitalData[i].name, width - 975, 50 + xoffset);

            // division
            stroke(150);
            line(width - 1000, 20 + xoffset, width, 20 + xoffset);
            line(width - 1000, 140 + xoffset + expanded, width, 140 + xoffset + expanded);

            // graph
            translate(0, -590 + xoffset + expanded / 2);
            stroke(vitalData[i].red, vitalData[i].green, vitalData[i].blue);
            for(int j = 1; j < width; j++){
                line(width - j, (height - 1 - vitalData[i].getY(j - 1) / 2),
                    width - 1 - j, (height - 1 - vitalData[i].getY(j) / 2));
            }
        }
        else{
            offset++;
        }

        popMatrix();
    }
}

void dispose() {
    noLoop();
    for(int i = 0; i < NODESNUM; i++){
        if(NODEENABLE[i]){
            serialPort[i].stop();
        }
    }
}

void sendData() {
    if(count % DEVIDECOUNT == 0){
        for(int i = 0; i < NODESNUM; i++){
            if(NODEENABLE[i]){
                serialPort[i].write(vitalData[i].txb);  // send byte data
                
                //println(vitalData[i].txb); //print the transmitted value
                
                //Save in a text file
                //---------------------------------------------
                //-> Milliseconds
                //output.println(time_msc + "\t" + vitalData[i].txb);
                
                //-> Minutes and seconds
                //output.println(min + ":" + sec + "\t" + vitalData[i].txb);
                //---------------------------------------------
                
                //Debug
                //println(graphCount + ", " + graphHeight);

                if(serialPort[i].available() > 0){
                    print(serialPort[i].read());
                }
            }
        }
    }

    count++;
}


//-------------------------------- stop writing ---------------------------------
void keyPressed() {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit(); // Stops the program
}
//--------------------------------------------------------------------------------


// ------------------------------------- Read CSV file ------------------------------------------
//sample data from CSV file
void initSampleData(String fileName){

    table = loadTable(fileName, "header");

    println(table.getRowCount() + " total rows in table");

    for(TableRow row : table.rows()){
        int[] value = new int[5];
        value[0] = row.getInt("'ECG lead V'");  // ECG lead
        value[1] = row.getInt("'ART'");         // Arterial
        value[2] = row.getInt("'Resp. Imp.'");  // Respiration
        value[3] = row.getInt("'PAP'");         // PAP
        value[4] = row.getInt("'CVP'");         // CVP

        for(int i = 0; i < 5; i++){
            if(value[i] < vitalData[i].min){
                vitalData[i].min = value[i];
            }

            if(value[i] > vitalData[i].max){
                vitalData[i].max = value[i];
            }
        }
    }

    for(int i = 0; i < 5; i++){
        if(vitalData[i].min < lowestSample){
            lowestSample = vitalData[i].min;
        }

        if(vitalData[i].max > highestSample){
            highestSample = vitalData[i].max;
        }
    }
}