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
  boardIP: string;
  step: (step1, step2, step3, step4, step5, step6);

implementation

{$R *.dfm}

uses settings;

procedure TfrmMain.btbSettingsClick(Sender: TObject);
var
  i: word;
begin
  i := stgSettings.Row;
  if i >0 then begin

  step := step4;

  try
//    IdUDPServer.Active := True;
    IdUDPServer.SendBuffer(mSettings[i-1].IP, $FFFF, Id_IPv4, ToBytes('D', en8Bit));
  except on e : Exception do
    memTerminal.Lines.Append('server error: ' + e.Message);
  end;
  end;
end;

procedure TfrmMain.btbSearchClick(Sender: TObject);
begin
//  SetLength(mSettings, 0);
  ShowSettings;

  step := step1;

  try
//    IdUDPServer.Active := True;
    IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('A', en8Bit));
  except on e : Exception do
    memTerminal.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  SetLength(mSettings, 0);
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  with stgSettings do begin
    Cells[0,0] := '¹';
    Cells[1,0] := 'IP';
    Cells[2,0] := 'MAC';
  end;

  ShowSettings();

  pgcMain.ActivePage := tbsSettings;
end;

procedure TfrmMain.IdUDPServerAfterBind(Sender: TObject);
begin
  memTerminal.Lines.Append('server after bind');
end;

procedure TfrmMain.IdUDPServerBeforeBind(AHandle: TIdSocketHandle);
begin
  memTerminal.Lines.Append('server before bind');
end;

procedure TfrmMain.IdUDPServerStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
begin
  memTerminal.Lines.Append('server status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServerUDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
begin
  memTerminal.Lines.Append('exception: ' + AMessage);
end;

function x(s: string): string;
var
  x: byte;
begin
  x := StrToInt(s);
  result := Chr(x);
end;

procedure TfrmMain.IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
var
  s: string;
  st: setting;
  s1,s2,s3:string;
  a:TStringDynArray;
  z:string;
begin
  try
    s := BytesToString(AData, Indy8BitEncoding);
    memTerminal.Lines.Add('server read: ' + s + ' IP='+ABinding.IP + ' peer IP='+ABinding.PeerIP + ' port='+IntToStr(ABinding.Port) + ' peer port='+IntToStr(ABinding.PeerPort));

    if step = step1 then begin
      memTerminal.Lines.Add('step 1');
      if s = 'B' then begin
        step := step2;

        boardIP := ABinding.PeerIP;
        memTerminal.Lines.Add('board IP = '+boardIP);

        IdUDPServer.SendBuffer(boardIP, $FFFF, Id_IPv4, ToBytes('C', en8Bit));
      end;
    end
    else if step = step2 then begin
      if ABinding.PeerIP = boardIP then begin
        memTerminal.Lines.Add('step 2');
        step := step3;

        st.IP := boardIP;
        st.MAC := s;

        SetLength(mSettings, Length(mSettings)+1);
        mSettings[Length(mSettings)-1] := st;

        ShowSettings;
      end;
    end
    else if step = step4 then begin
      memTerminal.Lines.Add('step 4');
      step := step5;

      if not Assigned(frmSettings) then frmSettings := frmSettings.Create(Self);
      with frmSettings do begin
        medIP.Text := IntToStr(AData[1])+'.'+IntToStr(AData[2])+'.'+IntToStr(AData[3])+'.'+IntToStr(AData[4]);
        medGateway.Text := IntToStr(AData[5])+'.'+IntToStr(AData[6])+'.'+IntToStr(AData[7])+'.'+IntToStr(AData[8]);
        medNetmask.Text := IntToStr(AData[9])+'.'+IntToStr(AData[10])+'.'+IntToStr(AData[11])+'.'+IntToStr(AData[12]);
      end;

      if frmSettings.ShowModal = mrOk then begin
        step := step6;

        with frmSettings do begin
          s1 := medIP.Text;
          s2 := medGateway.Text;
          s3 := medNetmask.Text;
        end;

        z := 'F';
        a := SplitString(s1,'.');
        z := z + x(a[0])+x(a[1])+x(a[2])+x(a[3]);
        a := SplitString(s2,'.');
        z := z + x(a[0])+x(a[1])+x(a[2])+x(a[3]);
        a := SplitString(s3,'.');
        z := z + x(a[0])+x(a[1])+x(a[2])+x(a[3]);

        IdUDPServer.SendBuffer(boardIP, $FFFF, Id_IPv4, ToBytes(z, en8Bit));
      end;
    end
    else begin
      memTerminal.Lines.Add('step ?');
    end;
  except on e : Exception do
    memTerminal.Lines.Append('server error: ' + e.Message);
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
