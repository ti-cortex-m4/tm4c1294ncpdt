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

var
  frmMain: TfrmMain;

  mSettings: array of setting;
  IP: string;
  step: (step1, step2, step3, step4, step5, step6);

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
    step := step4;
    IdUDPServer.SendBuffer(mSettings[i-1].IP, $FFFF, Id_IPv4, ToBytes('D', Indy8BitEncoding));
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

  IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('M', Indy8BitEncoding));
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

function SaveIP(s: string): string;
var
  a: TStringDynArray;
begin
  a := SplitString(s,'.');
  result := StringToChar(a[3]) + StringToChar(a[2]) + StringToChar(a[1]) + StringToChar(a[0]);
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
   AddTerminal('step 1');

   if ((Length(AData) = 1+6) and (AData[0] = Ord('A'))) then begin
     step := step2;

     IP := ABinding.PeerIP;
     AddTerminal('IP = '+IP);

     x.IP := IP;
     x.mbMAC := GetMAC(AData);

     SetLength(mSettings, Length(mSettings)+1);
     mSettings[Length(mSettings)-1] := x;
     ShowSettings;
   end;
  end
  else if step = step4 then begin
    AddTerminal('step 4');
    step := step5;

    if not Assigned(frmSettings) then frmSettings := TfrmSettings.Create(Self);
    with frmSettings do begin
      medIP.Text := ReadIP(AData, 1);
      medGateway.Text := ReadIP(AData, 5);
      medNetmask.Text := ReadIP(AData, 9);
    end;

    if frmSettings.ShowModal = mrOk then begin
      step := step6;

      with frmSettings do begin
        z := 'F' + SaveIP(medIP.Text) + SaveIP(medGateway.Text) + SaveIP(medNetmask.Text);
      end;

      IdUDPServer.SendBuffer(IP, $FFFF, Id_IPv4, ToBytes(z, Indy8BitEncoding));

      Delay(3000);
      btbSearchClick(self);
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
