//void rtesSystem()
//{
//  //display.showNumberHexEx(0xA000);
//  if(measuredPulsePerMin < 80 && stallVar == 0)
//  {
//    opening = 0;
//    freq = 0;
//  }
//  if(measuredPulsePerMin > 150 && stallVar == 0)
//  {
//    opening = 0;
//    freq = 0;
//  }
//  if(measuredPulsePerMin >= 80 && measuredPulsePerMin <= 150 && stallVar == 0)
//  {
//    opening = 100;
//    freq = 30000;
//    stallVar = 1;
//  }
//  rtesSystemTimer(opening, freq);  //(opening, frequency)
//}
//
//void rtesSystemTimer(unsigned long setOpening, unsigned long freq)
//{
//  rtesCurrentTime = millis();
//  if (rtesCurrentTime - rtesPreviousTime >= freq)
//  {
//    rtesPreviousTime = rtesCurrentTime;
//    stallVar = 0;
//  }
//  else
//  {
//    if (rtesCurrentTime - rtesPreviousTime < setOpening)
//    {
//      currentLimitedOut(1, 1, 1);  //(fuel,sol,wat)
//      if (pulseIncToggle == 1)
//      {
//        pulseInc++;
//        pulseIncToggle = 0;
//      }
//    }
//    else
//    {
//      currentLimitedOut(1, 0, 1);  //(fuel,sol,wat)
//      pulseIncToggle = 1;
//    }
//  }
//}
void rtesSystem()
{
  if (pulse_fuelToWaterRatioCount > pulse_fuelToWaterRatio && !sprayStarted)
  {
    prevSolOnTime = millis();
    //currentLimitedOut(fuelTrig, 1, waterTrig);
    digitalWrite(solenoidWater, HIGH);
    digitalWrite(motorWater, HIGH);
    sprayStarted = true;
  }
  else if (sprayStarted)
  {
    if (millis() - prevSolOnTime >= solenoidOnTime)
    {
      digitalWrite(solenoidWater, LOW);
      digitalWrite(motorWater, LOW);
      //currentLimitedOut(fuelTrig, 0, waterTrig);
      pulseInc++;
      sprayStarted = false;
    }
    if (pulse_fuelToWaterRatioCount >= pulse_fuelToWaterRatio + solenoidOnPulse + 1)
      pulse_fuelToWaterRatioCount = 1;
    //sprayStarted = false;
  }
  else
  {
    digitalWrite(solenoidWater, LOW);
    digitalWrite(motorWater, LOW);
  }
}
