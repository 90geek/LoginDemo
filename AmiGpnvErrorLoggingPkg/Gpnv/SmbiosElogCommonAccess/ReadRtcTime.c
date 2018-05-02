/** @file
  Header file for real time clock Declarations.

Copyright (c) 2006 - 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


/** @file ReadRtcTime.c
    Reading Time From RTC

**/


//----------------------------------------------------------------------

#include "ReadRtcTime.h"


/**
  Check if it is a leap year.

  @param    Time   The time to be checked.

  @retval   TRUE   It is a leap year.
  @retval   FALSE  It is NOT a leap year.
**/
BOOLEAN
IsLeapYear (
  IN EFI_TIME   *Time
  )
{
  if (Time->Year % 4 == 0) {
    if (Time->Year % 100 == 0) {
      if (Time->Year % 400 == 0) {
        return TRUE;
      } else {
        return FALSE;
      }
    } else {
      return TRUE;
    }
  } else {
    return FALSE;
  }
}

/**
  See if field Day of an EFI_TIME is correct.

  @param    Time   Its Day field is to be checked.

  @retval   TRUE   Day field of Time is correct.
  @retval   FALSE  Day field of Time is NOT correct.
**/
BOOLEAN
DayValid (
  IN  EFI_TIME  *Time
  )
{
  INTN  DayOfMonth[12];

  DayOfMonth[0] = 31;
  DayOfMonth[1] = 29;
  DayOfMonth[2] = 31;
  DayOfMonth[3] = 30;
  DayOfMonth[4] = 31;
  DayOfMonth[5] = 30;
  DayOfMonth[6] = 31;
  DayOfMonth[7] = 31;
  DayOfMonth[8] = 30;
  DayOfMonth[9] = 31;
  DayOfMonth[10] = 30;
  DayOfMonth[11] = 31;

  //
  // The validity of Time->Month field should be checked before
  //
  ASSERT (Time->Month >=1);
  ASSERT (Time->Month <=12);
  if (Time->Day < 1 ||
      Time->Day > DayOfMonth[Time->Month - 1] ||
      (Time->Month == 2 && (!IsLeapYear (Time) && Time->Day > 28))
      ) {
    return FALSE;
  }

  return TRUE;
}

/**
  Checks an 8-bit BCD value, and converts to an 8-bit value if valid.

  This function checks the 8-bit BCD value specified by Value.
  If valid, the function converts it to an 8-bit value and returns it.
  Otherwise, return 0xff.

  @param   Value The 8-bit BCD value to check and convert

  @return  The 8-bit value converted. Or 0xff if Value is invalid.

**/
UINT8
CheckAndConvertBcd8ToDecimal8 (
  IN  UINT8  Value
  )
{
  if ((Value < 0xa0) && ((Value & 0xf) < 0xa)) {
    return BcdToDecimal8 (Value);
  }

  return 0xff;
}

/**
  See if all fields of a variable of EFI_TIME type is correct.

  @param   Time   The time to be checked.

  @retval  EFI_INVALID_PARAMETER  Some fields of Time are not correct.
  @retval  EFI_SUCCESS            Time is a valid EFI_TIME variable.

**/
EFI_STATUS
RtcTimeFieldsValid (
  IN EFI_TIME *Time
  )
{
  if (Time->Year < 1980 ||
      Time->Year > 2079 ||
      Time->Month < 1 ||
      Time->Month > 12 ||
      (!DayValid (Time)) ||
      Time->Hour > 23 ||
      Time->Minute > 59 ||
      Time->Second > 59 ||
      Time->Nanosecond > 999999999 ||
      (!(Time->TimeZone == EFI_UNSPECIFIED_TIMEZONE || (Time->TimeZone >= -1440 && Time->TimeZone <= 1440))) ||
      ((Time->Daylight & (~(EFI_TIME_ADJUST_DAYLIGHT | EFI_TIME_IN_DAYLIGHT))) != 0)) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}


/**
  Converts time read from RTC to EFI_TIME format defined by UEFI spec.

  This function converts raw time data read from RTC to the EFI_TIME format
  defined by UEFI spec.
  If data mode of RTC is BCD, then converts it to decimal,
  If RTC is in 12-hour format, then converts it to 24-hour format.

  @param   Time       On input, the time data read from RTC to convert
                      On output, the time converted to UEFI format
  @param   Century    Value of century read from RTC.
  @param   RegisterB  Value of Register B of RTC, indicating data mode
                      and hour format.

  @retval  EFI_INVALID_PARAMETER  Parameters passed in are invalid.
  @retval  EFI_SUCCESS            Convert RTC time to EFI time successfully.

**/
EFI_STATUS
ConvertRtcTimeToEfiTime (
  IN OUT EFI_TIME        *Time,
  IN     UINT8           Century,
  IN     RTC_REGISTER_B  RegisterB
  )
{
  BOOLEAN IsPM;

  if ((Time->Hour & 0x80) != 0) {
    IsPM = TRUE;
  } else {
    IsPM = FALSE;
  }

  Time->Hour = (UINT8) (Time->Hour & 0x7f);

  if (RegisterB.Bits.Dm == 0) {
    Time->Year    = CheckAndConvertBcd8ToDecimal8 ((UINT8) Time->Year);
    Time->Month   = CheckAndConvertBcd8ToDecimal8 (Time->Month);
    Time->Day     = CheckAndConvertBcd8ToDecimal8 (Time->Day);
    Time->Hour    = CheckAndConvertBcd8ToDecimal8 (Time->Hour);
    Time->Minute  = CheckAndConvertBcd8ToDecimal8 (Time->Minute);
    Time->Second  = CheckAndConvertBcd8ToDecimal8 (Time->Second);
  }
  Century       = CheckAndConvertBcd8ToDecimal8 (Century);

  if (Time->Year == 0xff || Time->Month == 0xff || Time->Day == 0xff ||
      Time->Hour == 0xff || Time->Minute == 0xff || Time->Second == 0xff ||
      Century == 0xff) {
    return EFI_INVALID_PARAMETER;
  }

  Time->Year = (UINT16) (Century * 100 + Time->Year);

  //
  // If time is in 12 hour format, convert it to 24 hour format
  //
  if (RegisterB.Bits.Mil == 0) {
    if (IsPM && Time->Hour < 12) {
      Time->Hour = (UINT8) (Time->Hour + 12);
    }

    if (!IsPM && Time->Hour == 12) {
      Time->Hour = 0;
    }
  }

  Time->Nanosecond  = 0;

  return EFI_SUCCESS;
}

/**
  Read RTC content through its registers.

  @param  Address  Address offset of RTC. It is recommended to use macros such as
                   RTC_ADDRESS_SECONDS.

  @return The data of UINT8 type read from RTC.
**/
UINT8
RtcRead (
  IN  UINT8 Address
  )
{
  IoWrite8 (PCAT_RTC_ADDRESS_REGISTER, (UINT8) (Address | (UINT8) (IoRead8 (PCAT_RTC_ADDRESS_REGISTER) & 0x80)));
  return IoRead8 (PCAT_RTC_DATA_REGISTER);
}

/**
  Wait for a period for the RTC to be ready.

  @param    Timeout  Tell how long it should take to wait.

  @retval   EFI_DEVICE_ERROR   RTC device error.
  @retval   EFI_SUCCESS        RTC is updated and ready.  
**/
EFI_STATUS
RtcWaitToUpdate (
  UINTN Timeout
  )
{
  RTC_REGISTER_A  RegisterA;
  RTC_REGISTER_D  RegisterD;

  //
  // See if the RTC is functioning correctly
  //
  RegisterD.Data = RtcRead (RTC_ADDRESS_REGISTER_D);

  if (RegisterD.Bits.Vrt == 0) {
    return EFI_DEVICE_ERROR;
  }
  //
  // Wait for up to 0.1 seconds for the RTC to be ready.
  //
  Timeout         = (Timeout / 10) + 1;
  RegisterA.Data  = RtcRead (RTC_ADDRESS_REGISTER_A);
 
  while (RegisterA.Bits.Uip == 1 && Timeout > 0) {
    MicroSecondDelay (10);
    RegisterA.Data = RtcRead (RTC_ADDRESS_REGISTER_A);
    Timeout--;
  }

  RegisterD.Data = RtcRead (RTC_ADDRESS_REGISTER_D);
  if (Timeout == 0 || RegisterD.Bits.Vrt == 0) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}


/**
  Convert RTC Read value of TIME in BCD Format.

  @param   Time       On input, the time data read from RTC to convert
                      On output, the time converted to BCD format

**/
VOID
ConvertFinaltoBCD(
  OUT  EFI_TIME               *Time
		  )
{
	Time->Year = (( (Time->Year % 100) / 10) * 0x10) + ((Time->Year % 100) % 10);
	Time->Month = (( (Time->Month) / 10) * 0x10) + ((Time->Month) % 10);
	Time->Day = (( (Time->Day) / 10) * 0x10) + ((Time->Day) % 10);
	Time->Hour = (( (Time->Hour) / 10) * 0x10) + ((Time->Hour) % 10);
	Time->Minute = (( (Time->Minute) / 10) * 0x10) + ((Time->Minute) % 10);
	Time->Second = (( (Time->Second) / 10) * 0x10) + ((Time->Second) % 10);
}


EFI_STATUS
GpnvRtcGetTime (
  OUT  EFI_TIME               *Time
  )
{
  EFI_STATUS      Status;
  RTC_REGISTER_B  RegisterB;
  UINT8           Century;

  //
  // Check parameters for null pointer
  //
  if (Time == NULL) {
    return EFI_INVALID_PARAMETER;

  }
  //
  // Wait for up to 0.1 seconds for the RTC to be updated
  //
  Status = RtcWaitToUpdate (PcdGet32 (PcdRealTimeClockUpdateTimeout));
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Read Register B
  //
  RegisterB.Data = RtcRead (RTC_ADDRESS_REGISTER_B);

  //
  // Get the Time/Date/Daylight Savings values.
  //
  Time->Second  = RtcRead (RTC_ADDRESS_SECONDS);
  Time->Minute  = RtcRead (RTC_ADDRESS_MINUTES);
  Time->Hour    = RtcRead (RTC_ADDRESS_HOURS);
  Time->Day     = RtcRead (RTC_ADDRESS_DAY_OF_THE_MONTH);
  Time->Month   = RtcRead (RTC_ADDRESS_MONTH);
  Time->Year    = RtcRead (RTC_ADDRESS_YEAR);

  Century = RtcRead (RTC_ADDRESS_CENTURY);
  
  //
  // Make sure all field values are in correct range
  //
  Status = ConvertRtcTimeToEfiTime (Time, Century, RegisterB);
  if (!EFI_ERROR (Status)) {
    Status = RtcTimeFieldsValid (Time);
  }
  if (EFI_ERROR (Status)) {
    return EFI_DEVICE_ERROR;
  }

  Century = CheckAndConvertBcd8ToDecimal8 (Century);
  Time->Year = Time->Year - (Century * 100); // Subtracting Century as GPNV doesn't need Century
  
  ConvertFinaltoBCD(Time);
  
  return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
