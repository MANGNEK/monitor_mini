void Display() {
  
  /* Display background */
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("CPU");
  display.setCursor(0, 38);
  display.println("GPU");
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,56);
  display.print("RAM Used");
  
  /*CPU/GPU/RAM  Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
  display.fillRect(77, 0, 52 , 9, BLACK);
  display.fillRect(38, 9, 90, 17, BLACK); // fill CPU live stats section only
  display.fillRect(77, 27, 52 , 9, BLACK);
  display.fillRect(38, 37, 90, 17, BLACK); // fill GPU live stats section only
  display.fillRect(52, 55, 36, 9, BLACK); // fill RAM live stats section only

  /*CPU & GPU Hardware ID*/
  
  if (inputString.indexOf("CPU") > -1)
  {
    String cpuName = "";
    display.setTextSize(1);
    display.setCursor(0, 0);

    int cpuNameStart = inputString.indexOf("CPU:");
    if (inputString.indexOf("Intel", cpuNameStart) > -1) {
      cpuNameStart = cpuNameStart + 10;
    }
    else {
      cpuNameStart = cpuNameStart + 8;
    }
    if (inputString.indexOf("GPU") > -1)
    {
      cpuName = inputString.substring(cpuNameStart, inputString.indexOf("GPU:"));
    }
    else
      cpuName = inputString.substring(cpuNameStart);
    display.print(cpuName);
  }
  
  if (inputString.indexOf("GPU") > -1)
  {
    display.setTextSize(0);

    display.setCursor(0, 28);
    //display.setCursor(-41, 28); // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
    int gpuNameStart = inputString.indexOf("GPU:");
    if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
      gpuNameStart = gpuNameStart + 11;
    }
    else {
      gpuNameStart = gpuNameStart + 8;
    }
    int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
    String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
    display.print(gpuName);
  }

  /*CPU Freq Display String*/
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

  /*CPU Core Freq*/
  display.setCursor(86,0);
  display.print(cpuClockString);
  display.println("MHz");

  /*CPU Display String*/
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

  /*CPU Load, All Core*/
  display.setCursor(30, 10);
  display.setTextSize(2);
  display.print(cpuString2);
  display.setTextSize(1);
  display.print("%");         // Small Percent Symbol

  /*CPU Temperature*/
  display.setCursor(92,10);
  display.setTextSize(2);
  display.print(cpuString1);
  display.setTextSize(1);
  display.print((char)247);   //Degrees Symbol
  display.println("C");       // Centigrade Symbol
  
  /*GPU Core Freq*/
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

  /*GPU Core Freq*/
  if (gpuCoreClockString.length() < 4) {
    display.setCursor(92,28);
  } else {
    display.setCursor(86,28);
  }
  display.print(gpuCoreClockString);
  display.println("MHz");       // Centigrade Symbol
  
  /*GPU Display String*/
  int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);
  
  /*GPU Load*/
  display.setCursor(30,38);
  display.setTextSize(2);
  display.print(gpuString2);
  display.setTextSize(1);
  display.print("%");       // Small Percent Symbol
  
  /*GPU Temperature*/
  if (gpuString1.length() < 2) {
    display.setCursor(104,38);
  } else {
    display.setCursor(92,38);
  }
  display.setTextSize(2);
  display.print(gpuString1);
  display.setTextSize(1);
  display.print((char)247);   //Degrees Symbol
  display.println("C");       // Centigrade Symbol
  
  /*SYSTEM RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString = inputString.substring(ramStringStart + 1 , ramStringLimit);

  /*RAM Usage*/
  display.setCursor(56,56);
  display.print(ramString);
  display.print("B");
  
  display.display();
}
