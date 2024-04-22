#include <ModbusMaster.h>//modbus库
#include <SoftwareSerial.h>

ModbusMaster sensor_node;//modbus主机节点定义
ModbusMaster drive_node;
SoftwareSerial computerSerial(2, 3);//软串口定义

const int preloadPIN = 12;
const int resetPIN = 13;

static int previousLoad = LOW;
static int previousReset = LOW;
int State = 0;//用于标志当前驱动器状态以互斥运动

void setup() {
  
  Serial.begin(19200); //目前用来作为调试的串口与电脑连接
  
  computerSerial.begin(19200); //目前是连接了设备通讯总线

  sensor_node.begin(1,computerSerial); //定义传感器机号，这个地方后续可能得改成Serial

  drive_node.begin(2,computerSerial); //定义驱动器机号

  pinMode(preloadPIN, INPUT);

  pinMode(resetPIN, INPUT);

  
}

void upCommand(){
  
  uint8_t result1,result2,result3;

  result1 = drive_node.writeSingleRegister(1307,0);//P5-27写0
  if(result1 == drive_node.ku8MBSuccess){
    result2 = drive_node.writeSingleRegister(1308,0);//P5-28写0
    if(result2 == drive_node.ku8MBSuccess){
      result3 = drive_node.writeSingleRegister(8453,1);//F1-05写1使能
      if(result3 == drive_node.ku8MBSuccess){
        ;//这里放置传递给上位机完成上升指令的代码
      }
      else{
        Serial.print("Failed, result3 error code: ");
        Serial.println(result3, HEX);
        ;//这里放置传递给上位机指令3错误的代码
      }
    }
    else{
      Serial.print("Failed, result2 error code: ");
      Serial.println(result2, HEX);
      ;//这里放置传递给上位机指令2错误的代码
    }
  }
  else{
    Serial.print("Failed, result1 error code: ");
    Serial.println(result1, HEX);
    ;//这里放置传递给上位机指令1错误的代码
  }

}

void resetCommand(){

  uint8_t result1,result2,result3;

  result1 = drive_node.writeSingleRegister(1307,1);//P5-27写1
  if(result1 == drive_node.ku8MBSuccess){
    result2 = drive_node.writeSingleRegister(1308,1);//P5-28写1
    if(result2 == drive_node.ku8MBSuccess){
      result3 = drive_node.writeSingleRegister(8453,1);//F1-05写1使能
      if(result3 == drive_node.ku8MBSuccess){
        ;//这里放置传递给上位机完成上升指令的代码
      }
      else{
        Serial.print("Failed, result3 error code: ");
        Serial.println(result3, HEX);
        ;//这里放置传递给上位机指令3错误的代码
      }
    }
    else{
      Serial.print("Failed, result2 error code: ");
      Serial.println(result2, HEX);
      ;//这里放置传递给上位机指令2错误的代码
    }
  }
  else{
    Serial.print("Failed, result1 error code: ");
    Serial.println(result1, HEX);
    ;//这里放置传递给上位机指令1错误的代码
  }

}

void stopCommand(){

  uint8_t result;

  result = drive_node.writeSingleRegister(8453,0);//F1-05写0不使能

  if(result == drive_node.ku8MBSuccess){
        ;//这里放置传递给上位机完成上升指令的代码
      }
      else{
        Serial.print("Failed, result error code: ");
        Serial.println(result, HEX);
        ;//这里放置传递给上位机指令错误的代码
      }
}

void preloadCommand(){

  uint8_t result1,result2,result3;

  result1 = drive_node.writeSingleRegister(1307,0);//P5-27写0
  if(result1 == drive_node.ku8MBSuccess){
    result2 = drive_node.writeSingleRegister(1308,1);//P5-28写1
    if(result2 == drive_node.ku8MBSuccess){
      result3 = drive_node.writeSingleRegister(8453,1);//F1-05写1使能
      if(result3 == drive_node.ku8MBSuccess){
        ;//这里放置传递给上位机完成上升指令的代码
      }
      else{
        Serial.print("Failed, result3 error code: ");
        Serial.println(result3, HEX);
        ;//这里放置传递给上位机指令3错误的代码
      }
    }
    else{
      Serial.print("Failed, result2 error code: ");
      Serial.println(result2, HEX);
      ;//这里放置传递给上位机指令2错误的代码
    }
  }
  else{
    Serial.print("Failed, result1 error code: ");
    Serial.println(result1, HEX);
    ;//这里放置传递给上位机指令1错误的代码
  }
}

void speadCommand(){
  
  uint8_t result;

  result = drive_node.readHoldingRegisters(4096, 2);  // 读4096地址开始的2个寄存器
  uint16_t data[2];  // 存储结果

  if (result == drive_node.ku8MBSuccess) {

    data[0]=drive_node.getResponseBuffer(0);
    data[1]=drive_node.getResponseBuffer(1);//读对应Buffer的值

    uint32_t combinedValue = (static_cast<uint32_t>(data[0]) << 16) | data[1];//合并该值

    int decimalValue = static_cast<int>(combinedValue); //转化为十进制
    
    Serial.print("Data read: ");
    Serial.println(decimalValue); //这里后续放蓝牙协议
  } else {
    Serial.print("Failed, error code: ");
    Serial.println(result, HEX); //后续放传输给上位机的内容
  }

}

void readCommand(){
  
  uint8_t result; //存储结果状态
  uint16_t data[2];  // 存储结果

  result = sensor_node.readHoldingRegisters(2000, 2);  // 读2000地址开始的2个寄存器

  if (result == sensor_node.ku8MBSuccess) {

    data[0]=sensor_node.getResponseBuffer(0);
    data[1]=sensor_node.getResponseBuffer(1);//读对应Buffer的值

    uint32_t combinedValue = (static_cast<uint32_t>(data[0]) << 16) | data[1];//合并该值

    int decimalValue = static_cast<int>(combinedValue); //转化为十进制

    if (decimalValue > 61440){
      decimalValue = decimalValue -65536;
    }//由于量程一般不会达到六百多，因此大于F000的直接用补码表示就是负数了。

    double num = decimalValue;
    num = num /100;
    
    Serial.print("Data read: ");
    Serial.println(num); //这里后续放蓝牙协议
  } else {
    Serial.print("Failed, error code: ");
    Serial.println(result, HEX);
  }

}

void loop() {
  
  int currentLoad = digitalRead(preloadPIN);
  int currentReset = digitalRead(resetPIN);

  if(currentLoad != previousLoad){ //按下预紧按钮的逻辑，按钮常断
    if(currentLoad == HIGH && State != 2){
      preloadCommand();
      State = 1;
    }
    else if(currentLoad == LOW && State !=2){
      stopCommand();
      State = 0;
    }
  }

  if(currentReset != previousReset){ //按下复位按钮的逻辑，按钮常断
    if(currentReset == HIGH && State !=1){
      resetCommand();
      State = 2;
    }
    else if(currentReset == LOW && State !=1){
      stopCommand();
      State = 0;
    }
  }
  
  delay(100);
  //测试代码
  // if(Serial.available()){
  //   delay(100);
  //   while (Serial.available()) {
  //       Serial.read(); // 读取并丢弃剩余的字符
  //   }
  //   upCommand();
  // }
  
}

