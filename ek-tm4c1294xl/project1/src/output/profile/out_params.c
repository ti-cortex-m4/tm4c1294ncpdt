/*------------------------------------------------------------------------------
OUT_PARAMS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../serial/ports.h"
#include        "../../digitals/params/params.h"


/*
      case bINQ_GETPARAM_100:
        if ((uint)100*bInBuff5 < wPARAMS)
        {
          InitPushCRC();
          Push(&mpdiParam[ (uint)100*bInBuff5 ],(uint)100*sizeof(digital));

          Output((uint)100*sizeof(digital));
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_GETPARAM:
        if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
        {
          InitPushCRC();
          Push(&mpdiParam[ bInBuff5*0x100 + bInBuff6 ],sizeof(digital));

          Output(sizeof(digital));
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_SETPARAM:
        if (enGlobal != GLB_WORK)
        {
          if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
          {
            diT.ibPort   = InBuff(7);
            diT.ibPhone  = InBuff(8);
            diT.bDevice  = InBuff(9);
            diT.bAddress = InBuff(10);
            diT.ibLine   = InBuff(11);

            if (TrueParam() == 1)
            {
              mpdiParam[ bInBuff5*0x100 + bInBuff6 ] = diT;
              LongResult(bRES_OK);
            }
            else Result(bRES_BADDATA);
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDREPROGRAM);
        break;

      case bINQ_GETDIVIDER:
        if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
        {
          InitPushCRC();
          Push(&mpreParamDiv[bInBuff5*0x100 + bInBuff6], sizeof(real));
          Output(sizeof(real));
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_SETDIVIDER:
        if (enGlobal != GLB_WORK)
        {
          if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
          {
            InitPop(7);

            PopReal();
            mpreParamDiv[bInBuff5*0x100 + bInBuff6] = reBuffA;

            LongResult(bRES_OK);
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDREPROGRAM);
        break;

      case bINQ_GETPARAMCURR:
        if ((uint)10*bInBuff5 < wPARAMS)
        {
          SaveDisplay();
          ShowHi(szDirectParam); Clear();

          InitPushCRC();
          Push(&tiCurr, sizeof(time));

          boBeginParam = boFalse;

          fAlt = 1;
          for (ibCan=0; ibCan<10; ibCan++)
          {
            sprintf(szHi+13,"%03u",(uint)10*bInBuff5+ibCan+1);

            if (fAlt == 1)
            {
              if (mpboEnblPar[(uint)10*bInBuff5+ibCan] != boTrue)
                reBuffA = 0;
              else
              {
                i = ibPort;
                fAlt = ReadParam((uint)10*bInBuff5+ibCan);
                ibPort = i;
              }
            }

            if (fAlt == 1)
              Push(&reBuffA, sizeof(real));
            else
            {
              PushChar(0xFF);
              PushChar(0xFF);
              PushChar(0xFF);
              PushChar(0xFF);
            }
          }

          Output(sizeof(time)+(uint)10*sizeof(real));
          NextPause();                                      // внимание !

          LoadDisplay();
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_GETPARAMBUFF:
        if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
        {
          InitPushCRC();

          Push(&mptiParBuff[ (uint)10*bInBuff5 ],              (uint)10*bInBuff6*sizeof(time));
          Push(&mpreParBuff[ ibSoftTim ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

          Output((uint)10*bInBuff6*(sizeof(time)+sizeof(real)));
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_GETPARAMFULL:
        if (enGlobal != GLB_PROGRAM)
        {
          if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
          {
            if (bInBuff7*0x100+bInBuff8 < wTIMES)
            {
              if (LoadParTim((wTIMES + iwHardTim - (bInBuff7*0x100+bInBuff8)) % wTIMES) == 1)
              {
                InitPushCRC();

                PushInt(iwHardTim);
                PushInt(wTIMES);
                PushChar(boQuickParam);
                Push(&tiCurr, sizeof(time));

                Push(&mpreParBuff[ PrevSoftTim() ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

                Output(5+sizeof(time)+(uint)10*bInBuff6*sizeof(real));
              }
              else Result(bRES_BADFLASH);
            }
            else Result(bRES_BADADDRESS);
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDWORK);
        break;

      case bINQ_RESETDIVIDERS:
        if (enGlobal != GLB_WORK)
        {
          MakeAllDividers();
          Result(bRES_OK);
        }
        else Result(bRES_NEEDREPROGRAM);
        break;

      case bINQ_GETPARAMDIG:
        if (bInBuff5 >= bCANALS)
          Result(bRES_BADADDRESS);
        else if ((GetDigitalPhone(bInBuff5) != 0) || (GetDigitalDevice(bInBuff5) == 0))
          Result(bRES_BADDIGITAL);
        else
        {
          SaveDisplay();
          ShowHi(szDirectParam); Clear();

          InitPushCRC();
          Push(&tiCurr, sizeof(time));

          boBeginParam = boFalse;

          fAlt = 1;
          for (ibCan=0; ibCan<bPARAM_BLOCK; ibCan++)
          {
            sprintf(szHi+14,"%2bu",ibCan+1);

            if (fAlt == 1)
            {
              diT.ibPort   = mpdiDigital[bInBuff5].ibPort;
              diT.ibPhone  = mpdiDigital[bInBuff5].ibPhone;
              diT.bDevice  = mpdiDigital[bInBuff5].bDevice;
              diT.bAddress = mpdiDigital[bInBuff5].bAddress;
              diT.ibLine   = mppaParamMap[ibCan];

              mpdiParam[wPARAMS-1] = diT;

              mpboEnblPar[wPARAMS-1] = boTrue;
              MakeDividers(wPARAMS-1);

              if (boParamDivider == boTrue)
              {
                wBuffD = GetParamIndex();
                if (wBuffD != 0xFFFF)
                  mpreParamDiv[wPARAMS-1] = mpreParamDiv[wBuffD];
              }

              if (mpboEnblPar[wPARAMS-1] != boTrue)
                reBuffA = 0;
              else
              {
                ibDig = bInBuff5;

                i = ibPort;
                fAlt = ReadParam(wPARAMS-1);
                ibPort = i;
              }
            }

            if (fAlt == 1)
              Push(&reBuffA, sizeof(real));
            else
            {
              PushChar(0xFF);
              PushChar(0xFF);
              PushChar(0xFF);
              PushChar(0xFF);
            }
          }

          Output(sizeof(time)+bPARAM_BLOCK*sizeof(real));
          NextPause();                                      // внимание !

          LoadDisplay();
        }
        break;
*/
