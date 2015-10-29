unit main;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons,
  IdUDPClient, IdBaseComponent, IdComponent, IdUDPBase, IdGlobal,IdUDPServer,
  IdSocketHandle, Vcl.ComCtrls, Vcl.Grids, Vcl.ExtCtrls;

type
  TfrmMain = class(TForm)
    IdUDPClient: TIdUDPClient;
    IdUDPServer: TIdUDPServer;
    PageControl1: TPageControl;
    tbsSettings: TTabSheet;
    tbsTerminal: TTabSheet;
    btbStartClient: TBitBtn;
    btbStopClient: TBitBtn;
    btbStartServer: TBitBtn;
    btbStopServer: TBitBtn;
    Memo1: TMemo;
    panSettingsRight: TPanel;
    panSettingsClient: TPanel;
    btbSearch: TBitBtn;
    stgSettings: TStringGrid;
    BitBtn1: TBitBtn;
    procedure btbStartClientClick(Sender: TObject);
    procedure IdUDPClientConnected(Sender: TObject);
    procedure IdUDPClientDisconnected(Sender: TObject);
    procedure IdUDPClientStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
    procedure btbStopClientClick(Sender: TObject);
    procedure btbStartServerClick(Sender: TObject);
    procedure IdUDPServerAfterBind(Sender: TObject);
    procedure IdUDPServerBeforeBind(AHandle: TIdSocketHandle);
    procedure IdUDPServerStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
    procedure IdUDPServerUDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
    procedure IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
    procedure FormCreate(Sender: TObject);
    procedure btbStopServerClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ShowSettings;
    procedure btbSearchClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
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

uses device;

procedure TfrmMain.BitBtn1Click(Sender: TObject);
begin

  step := step4;

  try
    IdUDPServer.Active := True;
    IdUDPServer.SendBuffer('192.168.1.100', $FFFF, Id_IPv4, ToBytes('D', en8Bit));
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.btbSearchClick(Sender: TObject);
begin
//  SetLength(mSettings, 0);
  ShowSettings;

  step := step1;

  try
    IdUDPServer.Active := True;
    IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('A', en8Bit));
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.btbStartClientClick(Sender: TObject);
var
received_data: TIdBytes;
i: integer;
begin
  try
    IdUDPClient.Active := True;
    IdUDPClient.Host := '192.168.1.255' ;//}'192.168.1.100';
    IdUDPClient.Port := $FFFF;
    IdUDPClient.Connect;
    if IdUDPClient.Connected  then
      begin
        IdUDPClient.Broadcast('X', $FFFF);

        SetLength(received_data, 100);
        i := IdUDPClient.ReceiveBuffer(received_data, 5000);
        Memo1.Lines.Add('Data received! Len:'+IntToStr(i)+', data:'+BytesToString(received_data, 0, i));
      end;


    IdUDPClient.Active := False;
  except on e : Exception do
    Memo1.Lines.Append('Error: ' + e.Message);
  end;
end;

procedure TfrmMain.btbStopClientClick(Sender: TObject);
begin
  IdUDPClient.Disconnect;
end;

procedure TfrmMain.btbStartServerClick(Sender: TObject);
begin
  step := step1;

  try
    IdUDPServer.Active := True;
    IdUDPServer.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('A', en8Bit));
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.btbStopServerClick(Sender: TObject);
begin
  IdUDPServer.Active := false;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  IdUDPServer.DefaultPort := $FFFF;
  IdUDPServer.Bindings.Add.IP := '0.0.0.0';

  SetLength(mSettings, 0);
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  with stgSettings do begin
    Cells[0,0] := '¹';
    Cells[1,0] := 'IP';
    Cells[2,0] := 'MAC';
  end;
end;

procedure TfrmMain.IdUDPClientConnected(Sender: TObject);
begin
   Memo1.Lines.Append('client connected');
end;

procedure TfrmMain.IdUDPClientDisconnected(Sender: TObject);
begin
   Memo1.Lines.Append('client disconnected');
end;

procedure TfrmMain.IdUDPClientStatus(ASender: TObject; const AStatus: TIdStatus;
  const AStatusText: string);
begin
   Memo1.Lines.Append('client status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServerAfterBind(Sender: TObject);
begin
  Memo1.Lines.Append('server after bind');
end;

procedure TfrmMain.IdUDPServerBeforeBind(AHandle: TIdSocketHandle);
begin
  Memo1.Lines.Append('server before bind');
end;

procedure TfrmMain.IdUDPServerStatus(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
begin
  Memo1.Lines.Append('server status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServerUDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
begin
  Memo1.Lines.Append('exception: ' + AMessage);
end;

procedure TfrmMain.IdUDPServerUDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
var
  s: string;
  st: setting;
  s1,s2,s3:string;
begin
  try
    s := BytesToString(AData, Indy8BitEncoding);
    Memo1.Lines.Add('server read: ' + s + ' IP='+ABinding.IP + ' peer IP='+ABinding.PeerIP + ' port='+IntToStr(ABinding.Port) + ' peer port='+IntToStr(ABinding.PeerPort));

    if step = step1 then begin
      Memo1.Lines.Add('step 1');
      if s = 'B' then begin
        step := step2;

        boardIP := ABinding.PeerIP;
        Memo1.Lines.Add('board IP = '+boardIP);

        IdUDPServer.SendBuffer(boardIP, $FFFF, Id_IPv4, ToBytes('C', en8Bit));
      end;
    end
    else if step = step2 then begin
      if ABinding.PeerIP = boardIP then begin
        Memo1.Lines.Add('step 2');
        step := step3;

        st.IP := boardIP;
        st.MAC := s;

        SetLength(mSettings, Length(mSettings)+1);
        mSettings[Length(mSettings)-1] := st;

        ShowSettings;
      end;
    end
    else if step = step4 then begin
      Memo1.Lines.Add('step 4');
      step := step5;

      if not Assigned(frmDevice) then frmDevice := TfrmDevice.Create(Self);
      with frmDevice do begin
        medIP.Text := IntToStr(AData[0])+'.'+IntToStr(AData[1])+'.'+IntToStr(AData[2])+'.'+IntToStr(AData[3]);
        medGateway.Text := IntToStr(AData[4])+'.'+IntToStr(AData[5])+'.'+IntToStr(AData[6])+'.'+IntToStr(AData[7]);
        medNetmask.Text := IntToStr(AData[8])+'.'+IntToStr(AData[9])+'.'+IntToStr(AData[10])+'.'+IntToStr(AData[11]);
      end;

      if frmDevice.ShowModal = mrOk then begin
        step := step6;

        with frmDevice do begin
          s1 := medIP.Text;
          s2 := medGateway.Text;
          s3 := medNetmask.Text;
        end;

        IdUDPServer.SendBuffer(boardIP, $FFFF, Id_IPv4, ToBytes('E', en8Bit));
      end;
    end
    else begin
      Memo1.Lines.Add('step ?');
    end;
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.ShowSettings;
var
  i: word;
begin
  if Length(mSettings) = 0 then begin
    stgSettings.RowCount := 2;
  end
  else begin
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
