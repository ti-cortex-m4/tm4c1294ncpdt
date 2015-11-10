unit main;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons,
  IdUDPClient, IdBaseComponent, IdComponent, IdUDPBase, IdGlobal,IdUDPServer,
  IdSocketHandle, Vcl.ComCtrls, Vcl.Grids, Vcl.ExtCtrls, StrUtils, System.Types;

type
  TfrmMain = class(TForm)
    IdUDPServer: TIdUDPServer;
    pgcMain: TPageControl;
    tbsSettings: TTabSheet;
    tbsTerminal: TTabSheet;
    memTerminal: TMemo;
    panSettingsRight: TPanel;
    panSettingsClient: TPanel;
    btbSearch: TBitBtn;
    stgSettings: TStringGrid;
    btbSettings: TBitBtn;
    procedure AddTerminal(s: string);
    procedure ErrBox(s: string);
    procedure WrnBox(s: string);
    procedure InfBox(s: string);
    procedure IdUDPServerAfterBind(Sender: TObject);
    procedure IdUDPServerBeforeBind(AHandle: TIdSocketHandle);
    procedure IdUDPServerStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
    procedure IdUDPServerUDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
    procedure IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ShowSettings;
    procedure btbSearchClick(Sender: TObject);
    procedure btbSettingsClick(Sender: TObject);
    procedure stgSettingsDblClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  mac = array[0..5] of byte;

  setting = record
    IP: string;
    mbMAC: mac;
  end;

  bytes4 = array[0..3] of byte;
  combo4 = record case byte of
    0: (siT:  longword);
    1: (mpbT: bytes4);
  end;

var
  frmMain: TfrmMain;

  mSettings: array of setting;
  PeerIP: string;

  dwIP,dwGateway,dwNetmask: string;
  wPort: word;

  step: (step1, step2, step3, step4, step5, step6, step7);
  wCode: word;

implementation

{$R *.dfm}

uses settings;

procedure TfrmMain.AddTerminal(s: string);
begin
  memTerminal.Lines.Add(s);
end;

procedure TfrmMain.ErrBox(s: string);
begin
  AddTerminal('Ошибка: '+s);
  Application.MessageBox(PChar(s + ' '), 'Ошибка', mb_Ok + mb_IconHand);
end;

procedure TfrmMain.WrnBox(s: string);
begin
  AddTerminal('Внимание: '+s);
  Application.MessageBox(PChar(s + ' '), 'Внимание', mb_Ok + mb_IconWarning);
end;

procedure TfrmMain.InfBox(s: string);
begin
  AddTerminal('Информация: '+s);
  Application.MessageBox(PChar(s + ' '), 'Информация', mb_Ok + mb_IconAsterisk);
end;

procedure TfrmMain.btbSettingsClick(Sender: TObject);
var
  i: word;
begin
  i := stgSettings.Row;
  if i > 0 then begin
    wCode := 0;
    PeerIP := mSettings[i-1].IP;

    step := step3;
    IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('I', Indy8BitEncoding));
  end;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  SetLength(mSettings, 0);
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  with stgSettings do begin
    Cells[0,0] := '№';
    Cells[1,0] := 'IP';
    Cells[2,0] := 'MAC';
  end;
  ShowSettings();

  pgcMain.ActivePage := tbsSettings;

  btbSearchClick(self);
end;

procedure TfrmMain.btbSearchClick(Sender: TObject);
begin
  SetLength(mSettings, 0);
  ShowSettings;

  step := step1;
  IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('I', Indy8BitEncoding));
end;

procedure TfrmMain.IdUDPServerAfterBind(Sender: TObject);
begin
  AddTerminal('// server: after bind');
end;

procedure TfrmMain.IdUDPServerBeforeBind(AHandle: TIdSocketHandle);
begin
  AddTerminal('// server: before bind');
end;

procedure TfrmMain.IdUDPServerStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
begin
  AddTerminal('// server status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServerUDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
begin
  ErrBox('Ошибка сервера: ' + AMessage);
end;

function ReadIP(AData: TArray<System.Byte>; i: word): string;
begin
  result := IntToStr(AData[i+3])+'.'+IntToStr(AData[i+2])+'.'+IntToStr(AData[i+1])+'.'+IntToStr(AData[i+0])
end;

function StringToChar(s: string): string;
begin
  result := Chr(StrToInt(s));
end;

function SaveIP(s: string): longword;
var
  a: TStringDynArray;
  b: combo4;
begin
  a := SplitString(s,'.');
  b.mpbT[0] := StrToInt(a[3]);
  b.mpbT[1] := StrToInt(a[2]);
  b.mpbT[2] := StrToInt(a[1]);
  b.mpbT[3] := StrToInt(a[0]);
  result := b.siT;
end;

procedure Delay(MSec: longword);
var
  FirstTickCount,Now: longword;
begin
  FirstTickCount := GetTickCount;
  repeat
    Application.ProcessMessages;
    Now := GetTickCount;
  until (Now - FirstTickCount >= MSec) or (Now < FirstTickCount);
end;

function GetMAC(AData: TArray<System.Byte>): mac;
var
  i: byte;
begin
  for i := 0 to 5 do
    result[i] := AData[i+1];
end;

function GetCombo4(AData: TArray<System.Byte>; i: byte): combo4;
begin
  result.mpbT[0] := AData[i+0];
  result.mpbT[1] := AData[i+1];
  result.mpbT[2] := AData[i+2];
  result.mpbT[3] := AData[i+3];
end;

function GetIP(AData: TArray<System.Byte>; i: byte): string;
var
  j: combo4;
begin
  j := GetCombo4(AData,i);
  result := IntToStr(j.mpbT[3])+'.'+IntToStr(j.mpbT[2])+'.'+IntToStr(j.mpbT[1])+'.'+IntToStr(j.mpbT[0]);
end;

function GetWord(AData: TArray<System.Byte>; i: word): word;
begin
  result := $100*AData[i+1]+AData[i+0];
end;

function GetReadLong(a: char): TIdBytes;
var
  x: TArray<System.Byte>;
begin
  SetLength(x, 5);
  x[0] := Ord('G');
  x[1] := Ord(a);
  x[2] := Ord('|');
  x[3] := wCode mod $100;
  x[4] := wCode div $100;
  result := x;
end;

function SetAll(s1,s2,s3,s4: string): TIdBytes;
var
  x: TArray<System.Byte>;
  dw1,dw2,dw3: longword;
  w: word;
begin
  dw1 := SaveIP(s1);
  dw2 := SaveIP(s2);
  dw3 := SaveIP(s3);
  w := StrToInt(s4);

  SetLength(x, 1+1+4+4+4+2+1+2);

  x[0] := Ord('S');
  x[1] := Ord('I');

  x[2] := (dw1 mod $10000) mod $100;
  x[3] := (dw1 mod $10000) div $100;
  x[4] := (dw1 div $10000) mod $100;
  x[5] := (dw1 div $10000) div $100;

  x[6] := (dw2 mod $10000) mod $100;
  x[7] := (dw2 mod $10000) div $100;
  x[8] := (dw2 div $10000) mod $100;
  x[9] := (dw2 div $10000) div $100;

  x[10] := (dw3 mod $10000) mod $100;
  x[11] := (dw3 mod $10000) div $100;
  x[12] := (dw3 div $10000) mod $100;
  x[13] := (dw3 div $10000) div $100;

  x[14] := w mod $100;
  x[15] := w div $100;

  x[16] := Ord('|');
  x[17] := wCode mod $100;
  x[18] := wCode div $100;

  result := x;
end;

procedure TfrmMain.IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
var
  s: string;
  x: setting;
  z: string;
  i: word;
begin
  z := '';
  for i := 0 to Length(AData)-1 do z := z + IntToHex(AData[i],2);

//  s := BytesToString(AData, Indy8BitEncoding);
  AddTerminal('// server read: ' + z + ' '+ABinding.IP+ ':'+IntToStr(ABinding.Port) + ' < '+ABinding.PeerIP  + ':'+IntToStr(ABinding.PeerPort));

  if step = step1 then begin
   if ((Length(AData) = 1+6+4) and (AData[0] = Ord('A'))) then begin
     AddTerminal('step 1');
     step := step2;

     AddTerminal('IP = '+ABinding.PeerIP);

     x.IP := ABinding.PeerIP;
     x.mbMAC := GetMAC(AData);

     SetLength(mSettings, Length(mSettings)+1);
     mSettings[Length(mSettings)-1] := x;
     ShowSettings;
   end;
  end
  else if step = step3 then begin
    if ((Length(AData) = 1+6+4) and (AData[0] = Ord('A')) and (PeerIP = ABinding.PeerIP)) then begin
      AddTerminal('step 3');
      step := step6;
      IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, GetReadLong('I'));
    end;
  end
  else if step = step6 then begin
    if ((Length(AData) = 16+2) and (AData[0] = Ord('A')) and (PeerIP = ABinding.PeerIP)) then begin
      AddTerminal('step 6');
      step := step7;
      dwIP := GetIP(AData, 1);
      dwGateway := GetIP(AData, 5);
      dwNetmask := GetIP(AData, 9);
      wPort := GetWord(AData, 13);
      Inc(wCode);

    if not Assigned(frmSettings) then frmSettings := TfrmSettings.Create(Self);
    with frmSettings do begin
      medIP.Text := dwIP;
      medGateway.Text := dwGateway;
      medNetmask.Text := dwNetmask;
      medPort.Text := IntToStr(wPort);
    end;

    if frmSettings.ShowModal = mrOk then begin
      step := step6;

      with frmSettings do begin
        IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, SetAll(medIP.Text, medGateway.Text, medNetmask.Text, medPort.Text));
      end;

      Delay(2000);
      btbSearchClick(self);
    end;
    end;
  end

  else begin
    AddTerminal('step ?');
  end;
end;

function MACToStr(mbMAC: mac):string;
begin
  result := IntToStr(mbMAC[0])+'.'+
  IntToStr(mbMAC[1])+'.'+
  IntToStr(mbMAC[2])+'.'+
  IntToStr(mbMAC[3])+'.'+
  IntToStr(mbMAC[4])+'.'+
  IntToStr(mbMAC[5]);
end;

procedure TfrmMain.ShowSettings;
var
  i: word;
begin
  if Length(mSettings) = 0 then begin
    btbSettings.Enabled := false;
    stgSettings.RowCount := 2;
  end
  else begin
    btbSettings.Enabled := true;
    stgSettings.RowCount := Length(mSettings)+1;
    for i := 0 to Length(mSettings)-1 do begin
      with stgSettings do begin
        Cells[0,i+1] := IntToStr(i+1);
        Cells[1,i+1] := mSettings[i].IP;
        Cells[2,i+1] := MACToStr(mSettings[i].mbMAC);
      end;
    end;
  end;
end;

procedure TfrmMain.stgSettingsDblClick(Sender: TObject);
begin
  btbSettingsClick(self);
end;

end.
