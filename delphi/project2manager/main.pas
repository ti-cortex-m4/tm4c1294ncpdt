unit main;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons,
  IdUDPClient, IdBaseComponent, IdComponent, IdUDPBase, IdGlobal,IdUDPServer,
  IdSocketHandle;

type
  TfrmMain = class(TForm)
    IdUDPClient1: TIdUDPClient;
    BitBtn1: TBitBtn;
    Memo1: TMemo;
    BitBtn2: TBitBtn;
    IdUDPServer1: TIdUDPServer;
    BitBtn3: TBitBtn;
    BitBtn4: TBitBtn;
    procedure BitBtn1Click(Sender: TObject);
    procedure IdUDPClient1Connected(Sender: TObject);
    procedure IdUDPClient1Disconnected(Sender: TObject);
    procedure IdUDPClient1Status(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure IdUDPServer1AfterBind(Sender: TObject);
    procedure IdUDPServer1BeforeBind(AHandle: TIdSocketHandle);
    procedure IdUDPServer1Status(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
    procedure IdUDPServer1UDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
    procedure IdUDPServer1UDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
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

procedure TfrmMain.BitBtn1Click(Sender: TObject);
var
received_data: TIdBytes;
i: integer;
begin
  try
    IdUDPClient1.Active := True;
    IdUDPClient1.Host := '192.168.1.255' ;//}'192.168.1.100';
    IdUDPClient1.Port := $FFFF;
    IdUDPClient1.Connect;
    if IdUDPClient1.Connected  then
      begin
        IdUDPClient1.Broadcast('X', $FFFF);

        SetLength(received_data, 100);
        i := IdUDPClient1.ReceiveBuffer(received_data, 5000);
        Memo1.Lines.Add('Data received! Len:'+IntToStr(i)+', data:'+BytesToString(received_data, 0, i));
      end;


    IdUDPClient1.Active := False;
  except on e : Exception do
    Memo1.Lines.Append('Error: ' + e.Message);
  end;
end;

procedure TfrmMain.BitBtn2Click(Sender: TObject);
begin
  IdUDPClient1.Disconnect;
end;

procedure TfrmMain.BitBtn3Click(Sender: TObject);
begin
  step := step1;

  try
    IdUDPServer1.Active := True;
    IdUDPServer1.SendBuffer('255.255.255.255', $FFFF, Id_IPv4, ToBytes('A', en8Bit));
  except on e : Exception do
    Memo1.Lines.Append('server error: ' + e.Message);
  end;
end;

procedure TfrmMain.BitBtn4Click(Sender: TObject);
begin
  IdUDPServer1.Active := false;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  IdUDPServer1.DefaultPort := $FFFF;
  IdUDPServer1.Bindings.Add.IP := '0.0.0.0';
end;

procedure TfrmMain.IdUDPClient1Connected(Sender: TObject);
begin
   Memo1.Lines.Append('client connected');
end;

procedure TfrmMain.IdUDPClient1Disconnected(Sender: TObject);
begin
   Memo1.Lines.Append('client disconnected');
end;

procedure TfrmMain.IdUDPClient1Status(ASender: TObject; const AStatus: TIdStatus;
  const AStatusText: string);
begin
   Memo1.Lines.Append('client status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServer1AfterBind(Sender: TObject);
begin
  Memo1.Lines.Append('server after bind');
end;

procedure TfrmMain.IdUDPServer1BeforeBind(AHandle: TIdSocketHandle);
begin
  Memo1.Lines.Append('server before bind');
end;

procedure TfrmMain.IdUDPServer1Status(ASender: TObject; const AStatus: TIdStatus; const AStatusText: string);
begin
  Memo1.Lines.Append('server status: ' + AStatusText);
end;

procedure TfrmMain.IdUDPServer1UDPException(AThread: TIdUDPListenerThread; ABinding: TIdSocketHandle; const AMessage: string; const AExceptionClass: TClass);
begin
  Memo1.Lines.Append('exception: ' + AMessage);
end;

procedure TfrmMain.IdUDPServer1UDPRead(AThread: TIdUDPListenerThread; AData: TArray<System.Byte>; ABinding: TIdSocketHandle);
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

        IdUDPServer1.SendBuffer(boardIP, $FFFF, Id_IPv4, ToBytes('C', en8Bit));
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
