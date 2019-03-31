// *** Receive ***

// This 1st example will make the PC toggle the integrated led on the arduino board. 
// It demonstrates how to:
// - Define commands
// - Set up a serial connection
// - Receive a command with a parameter from the PC

#include <CmdMessenger.h> 
#include <Adafruit_NeoPixel.h>
#include <MemoryFree.h>

#define PIN            6
#define NUMPIXELS      144
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



CmdMessenger cmdMessenger = CmdMessenger(Serial);


// Commands
enum
{
  changeLed,
  dimmLed,
};


// Callbacks define on which received commands we take action 
void attachCommandCallbacks()
{
  cmdMessenger.attach(changeLed, OnChangeLed);
  cmdMessenger.attach(dimmLed, OnDimmLed);
  cmdMessenger.attach(OnUnknownCommand);
}

float transformInterval(float A, float B, float a, float b, float val) {
  return (val)*(b)/(B) ;
}


class Operation {
public:
    virtual void execute() = 0;
    virtual bool isFinished() = 0;
};

class ChangeLedOperation: public Operation {
private:
    int led;
    int r;
    int g;
    int b;

public:

    ChangeLedOperation(int led, int r, int g, int b) {
        this->led = led;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void execute() override {
        Serial.println("Execute ChangeLedOperation");
        pixels.setPixelColor(led, pixels.Color(r,g,b));
    }

    bool isFinished() override {
      pixels.show();
      return true;
    }
};

class DimmLedOperation: public Operation {
private:
    int led;
    int r;
    int g;
    int b;
    unsigned long startTime; // microseconds
    unsigned long duration; // microseconds
    int counter = 0;

public:

    DimmLedOperation(int led, int r, int g, int b, unsigned long duration) {
        // Transform to microseconds
        
        this->led = led;
        this->r = r;
        this->g = g;
        this->b = b;
        this->duration = duration;
        this->startTime = micros();
       
    }

    void execute() override {
         Serial.println("Execute DimmLedOperation");
         unsigned long passedTime = ( micros() - this->startTime ) * 4;
         float tFactorR = transformInterval(0, duration, 0, r, passedTime);
         float tFactorG = transformInterval(0, duration, 0, g, passedTime);
         float tFactorB = transformInterval(0, duration, 0, b, passedTime);
         float newR = r - tFactorR;
         float newG = g - tFactorG;
         float newB = b - tFactorB;

         pixels.setPixelColor(led, pixels.Color(newR,newG,newB));
         //pixels.show();
    }

    bool isFinished() override {
        unsigned long passedTime = ( micros() - this->startTime ) * 4;
        if(passedTime > duration) {
          pixels.setPixelColor(led, pixels.Color(0, 0, 0));
          pixels.show();
          return true;
        }
        return false;
    }
};

class SLLNode {
public:
    Operation* operation;
    SLLNode* next;

    SLLNode(Operation* operation, SLLNode* next){
        this->operation = operation;
        this->next = next;
    }

    SLLNode(Operation* operation){
        this->operation = operation;
        this->next = nullptr;
    }

    ~SLLNode() {
        delete operation;
    }
};



class SLL {
private:
    SLLNode *head;
    SLLNode *tail;

public:
    SLL() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void add(Operation *operation) {
        if(this->head == nullptr && this->tail == nullptr) {
            this->head = new SLLNode(operation);
            this->tail = this->head;
            return;
        }

        this->tail->next = new SLLNode(operation);
        this->tail = this->tail->next;
    }

    void compute() {
        if(this->head == nullptr)
            return;

        // Get the current operation
        SLLNode *crtNode = this->head;

        // Execute the operation
        crtNode->operation->execute();

        // If the operation is finished delete the node
        if(crtNode->operation->isFinished()) {
            this->head = this->head->next;
            if(crtNode == this->tail)
                this->tail = nullptr;

            delete crtNode;
        } else {
            // Otherwise keep it in the loop
            if(this->head == this->tail)
                return;

            this->head = this->head->next;
            this->tail->next = crtNode;
            this->tail = crtNode;
            this->tail->next = nullptr; 
        }

    }


};
       
void OnUnknownCommand()
{
  // LED
  pixels.setPixelColor(50, pixels.Color(255, 0,255));
  pixels.show(); // This sends the updated pixel color to the hardware.
}

// The sll of operations
SLL sllOp = SLL();

// Callback function that changes a led's color
void OnChangeLed()
{
  // Params:
  // led: int 0 - 143
  // r: red 0 - 255
  // g: green 0 - 255
  // b: blue 0 - 255

  // changes the color of the led to the parameters above
  
  int led = cmdMessenger.readInt32Arg();
  int r = cmdMessenger.readInt32Arg();
  int g = cmdMessenger.readInt32Arg();
  int b = cmdMessenger.readInt32Arg();

  Serial.print(led); Serial.print(" ");
  Serial.print(r); Serial.print(" ");
  Serial.print(g); Serial.print(" ");
  Serial.print(b); Serial.print(" ");
  Serial.println();
  
  sllOp.add(new ChangeLedOperation(led, r, g, b) );
}

void OnDimmLed()
{
  // Params:
  // led: int 0 - 143
  // r: red 0 - 255
  // g: green 0 - 255
  // b: blue 0 - 255
  // ms: miliseconds to dimm

  // changes the color of the led to the parameters above

  int led = cmdMessenger.readInt32Arg();
  float r = cmdMessenger.readInt32Arg(); float newR;
  float g = cmdMessenger.readInt32Arg(); float newG;
  float b = cmdMessenger.readInt32Arg(); float newB;
  int msAux = cmdMessenger.readInt32Arg();
  unsigned long ms = (unsigned long) msAux;
  unsigned long multiply = 1000;
  ms = ms * multiply;

  Serial.print(led); Serial.print(" ");
  Serial.print(r); Serial.print(" ");
  Serial.print(g); Serial.print(" ");
  Serial.print(b); Serial.print(" ");
  Serial.print(ms); Serial.print(" ");
  Serial.println();
  
  sllOp.add(new DimmLedOperation(led, r, g, b, ms) );
}


void setup() 
{
  // Listen on serial connection for messages from the PC
  // 115200 is the max speed on Arduino Uno, Mega, with AT8u2 USB
  // Use 57600 for the Arduino Duemilanove and others with FTDI Serial
  Serial.begin(115200); 

  // Start the pixel strip
  pixels.begin(); 

 
  // Adds newline to every command
  cmdMessenger.printLfCr();   

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();

}

// Loop function
void loop() 
{ 

  if(freeMemory() <= 0) {
    Serial.println("################################## ERROR NO MEMORY ###############################");
  }

  // Get In Serial Data
  cmdMessenger.feedinSerialData();

  // Change a light bulb
  sllOp.compute();
}
