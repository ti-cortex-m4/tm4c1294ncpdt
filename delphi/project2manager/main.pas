unit main;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons,
  IdUDPClient, IdBaseComponent, IdComponent, IdUDPBase, IdGlobal,IdUDPServer,
  IdSocketHandle;

type
  TfrmMain = class(TForm)
    IdUDPClient: TIdUDPClient;
    btbStartClient: TBitBtn;
    Memo1: TMemo;
    btbStopClient: TBitBtn;
    IdUDPServer: TIdUDPServer;
    btbStartServer: TBitBtn;
    btbStopServer: TBitBtn;
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
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;
  step: (step1, step2, step3);

implementation

{$R *.dfm}

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
  boardIP: string;
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
      end;
    end
    else begin
      Memo1.Lines.Add('step ?');
    end;
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

end.
