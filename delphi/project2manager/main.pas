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
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  setting = record
    IP: string;
    MAC: string;
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
  AddTerminal('������: '+s);
  Application.MessageBox(PChar(s + ' '), '������', mb_Ok + mb_IconHand);
end;

procedure TfrmMain.WrnBox(s: string);
begin
  AddTerminal('��������: '+s);
  Application.MessageBox(PChar(s + ' '), '��������', mb_Ok + mb_IconWarning);
end;

procedure TfrmMain.InfBox(s: string);
begin
  AddTerminal('����������: '+s);
  Application.MessageBox(PChar(s + ' '), '����������', mb_Ok + mb_IconAsterisk);
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
    Cells[0,0] := '�';
    Cells[1,0] := 'IP';
    Cells[2,0] := 'MAC';
  end;

  ShowSettings();

  pgcMain.ActivePage := tbsSettings;
end;

procedure TfrmMain.btbSearchClick(Sender: TObject);
begin
//  SetLength(mSettings, 0);
  ShowSettings;

  step := step1;

  IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('A', Indy8BitEncoding));
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
  ErrBox('������ �������: ' + AMessage);
end;

function ReadIP(AData: TArray<System.Byte>; i: word): string;
begin
  result := IntToStr(AData[i])+'.'+IntToStr(AData[i+1])+'.'+IntToStr(AData[i+2])+'.'+IntToStr(AData[i+3])
end;

function x(s: string): string;
begin
  result := Chr(StrToInt(s));
end;

function SaveIP(s: string): string;
var
  a: TStringDynArray;
begin
  a := SplitString(s,'.');
  result := x(a[0]) + x(a[1]) + x(a[2]) + x(a[3]);
end;

procedure TfrmMain.IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
var
  s: string;
  x: setting;
  z: string;
begin
  s := BytesToString(AData, Indy8BitEncoding);
  AddTerminal('// server read: ' + s + ' IP='+ABinding.IP + ' peer IP='+ABinding.PeerIP + ' port='+IntToStr(ABinding.Port) + ' peer port='+IntToStr(ABinding.PeerPort));

  if step = step1 then begin
    AddTerminal('step 1');
    if s = 'B' then begin
      step := step2;

      IP := ABinding.PeerIP;
      AddTerminal('IP = '+IP);

      IdUDPServer.SendBuffer(IP, $FFFF, Id_IPv4, ToBytes('C', Indy8BitEncoding));
    end;
  end
  else if step = step2 then begin
    if ABinding.PeerIP = IP then begin
      AddTerminal('step 2');
      step := step3;

      x.IP := IP;
      x.MAC := s;

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
    end;
  end
  else begin
    AddTerminal('step ?');
  end;
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
        Cells[2,i+1] := mSettings[i].MAC;
      end;
    end;
  end;
end;

end.
