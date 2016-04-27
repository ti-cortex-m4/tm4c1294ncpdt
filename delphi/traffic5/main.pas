unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, OoMisc, AdPort, IniFiles, Buttons;

type
  TfrmMain = class(TForm)
    panClient: TPanel;
    panBottom: TPanel;
    panLeft: TPanel;
    panRight: TPanel;
    Comm1: TApdComPort;
    Comm2: TApdComPort;
    cmbComm1: TComboBox;
    cmbBaud1: TComboBox;
    cmbComm2: TComboBox;
    cmbBaud2: TComboBox;
    lblComm1: TLabel;
    lblBaud1: TLabel;
    lblComm2: TLabel;
    lblBaud2: TLabel;
    spbLeft: TSpeedButton;
    spbRight: TSpeedButton;
    pgcMain: TPageControl;
    tbsTerminal: TTabSheet;
    tbsSettings: TTabSheet;
    memTerminal: TMemo;
    lblFlashDayTo: TLabel;
    edtFlashDayMax: TEdit;
    updProbability1: TUpDown;
    Label1: TLabel;
    Edit1: TEdit;
    updProbability2: TUpDown;
    Label2: TLabel;
    Edit2: TEdit;
    updProbability3: TUpDown;
    Timer1: TTimer;
    Edit3: TEdit;
    UpDown1: TUpDown;
    procedure FormResize(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SetBaud1(dwBaud: longint);
    procedure SetComm1(wComNumber: word);
    procedure SetBaud2(dwBaud: longint);
    procedure SetComm2(wComNumber: word);
    procedure ErrBox(stOut: string);
    procedure WrnBox(stOut: string);
    procedure InfBox(stOut: string);
    procedure Terminal(stT: string);
    procedure Ready(wComNumber: word; Count: word);
    procedure Dump(Count: word);
    function  Time(Time: TDateTime): string;
    function  Int2Str(wValue: word; bDigits: byte): string;
    procedure Buttons;
    procedure Comm1TriggerAvail(CP: TObject; Count: Word);
    procedure Comm2TriggerAvail(CP: TObject; Count: Word);
    procedure cmbComm1Change(Sender: TObject);
    procedure cmbComm2Change(Sender: TObject);
    procedure cmbBaud1Change(Sender: TObject);
    procedure cmbBaud2Change(Sender: TObject);
    procedure memTerminalKeyPress(Sender: TObject; var Key: Char);
    procedure spbLeftClick(Sender: TObject);
    procedure spbRightClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmMain:      TfrmMain;

  FIni:         TIniFile;

  mpbInBuff:            array[0..$FFFF] of byte;

  datStart,
  datStop,
  datNow:               TDateTime;
  wNumber:              word;

const
  stCOMM1:              string  = '���� �';
  stCOMM2:              string  = '���� �';
  stCOMNUMBER:          string  = '�����';
  stBAUD:               string  = '���������';
  stSETTINGS:           string  = '������';
  stPROBABILITY1:       string  = '�������������1';
  stPROBABILITY2:       string  = '�������������2';
  stPROBABILITY3:       string  = '�������������3';

  dwDEFAULT_BAUD:       longint = 9600;

implementation

{$R *.DFM}

procedure TfrmMain.FormResize(Sender: TObject);
begin
  if Height < 200 then Height := 200;
  if Width  < 500 then Width  := 500;

  panLeft.Width := panBottom.Width div 2;
end;

procedure TfrmMain.FormShow(Sender: TObject);
begin
  try
    FIni := TIniFile.Create(ExtractFilePath(ParamStr(0)) + 'traffic3.ini');

    SetComm1( FIni.ReadInteger(stCOMM1, stCOMNUMBER, 1) );
    SetBaud1( FIni.ReadInteger(stCOMM1, stBAUD,      dwDEFAULT_BAUD) );

    SetComm2( FIni.ReadInteger(stCOMM2, stCOMNUMBER, 2) );
    SetBaud2( FIni.ReadInteger(stCOMM2, stBAUD,      dwDEFAULT_BAUD) );

    updProbability1.Position := FIni.ReadInteger(stSETTINGS, stPROBABILITY1, 0);
    updProbability2.Position := FIni.ReadInteger(stSETTINGS, stPROBABILITY2, 0);
    updProbability3.Position := FIni.ReadInteger(stSETTINGS, stPROBABILITY3, 0);
  except
    ErrBox('������� ��� �������i ���������');
  end;

  with Comm1 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('��������� ����� ����� �: COM' + IntToStr(ComNumber));
      ComNumber := 1;
    end;
    cmbComm1.ItemIndex := ComNumber - 1;

    if cmbBaud1.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('���������� ��������� ����� �: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud1.ItemIndex := cmbBaud1.Items.IndexOf( IntToStr(Baud) );
  end;

  with Comm2 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('��������� ����� ����� �: COM' + IntToStr(ComNumber));
      ComNumber := 2;
    end;
    cmbComm2.ItemIndex := ComNumber - 1;

    if cmbBaud2.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('���������� ��������� ����� �: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud2.ItemIndex := cmbBaud2.Items.IndexOf( IntToStr(Baud) );
  end;

  Buttons;
  
  Comm1.Open := True;
  Comm2.Open := True;

  datStart := Now;
  datStop  := Now;
  datNow   := Now;

  pgcMain.ActivePage := tbsTerminal;
end;

procedure TfrmMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  try
    with Comm1 do begin
      FIni.WriteInteger(stCOMM1, stCOMNUMBER, ComNumber);
      FIni.WriteInteger(stCOMM1, stBAUD,      Baud);
    end;

    with Comm2 do begin
      FIni.WriteInteger(stCOMM2, stCOMNUMBER, ComNumber);
      FIni.WriteInteger(stCOMM2, stBAUD,      Baud);
    end;

    FIni.WriteInteger(stSETTINGS, stPROBABILITY1, updProbability1.Position);
    FIni.WriteInteger(stSETTINGS, stPROBABILITY2, updProbability2.Position);
    FIni.WriteInteger(stSETTINGS, stPROBABILITY3, updProbability3.Position);
  except
    ErrBox('������� ��� ���i������i ���������');
  end;
end;

procedure TfrmMain.SetComm1(wComNumber: word);
begin
  with Comm1 do begin
    try
      ComNumber := wComNumber;
    except
      ComNumber := 1;
      ErrBox('������� ��� ��������i ������ ����� �: COM' + IntToStr(wComNumber));
    end;
  end;
end;

procedure TfrmMain.SetBaud1(dwBaud: longint);
begin
  with Comm1 do begin
    try
      Baud := dwBaud;
    except
      Baud := dwDEFAULT_BAUD;
      ErrBox('������� ��� ��������i ��������i ����� �: ' + IntToStr(dwBaud));
    end;
  end;
end;

procedure TfrmMain.SetComm2(wComNumber: word);
begin
  with Comm2 do begin
    try
      ComNumber := wComNumber;
    except
      ComNumber := 2;
      ErrBox('������� ��� ��������i ������ ����� �: COM' + IntToStr(wComNumber));
    end;
  end;
end;

procedure TfrmMain.SetBaud2(dwBaud: longint);
begin
  with Comm2 do begin
    try
      Baud := dwBaud;
    except
      Baud := dwDEFAULT_BAUD;
      ErrBox('������� ��� ��������i ��������i ����� �: ' + IntToStr(dwBaud));
    end;
  end;
end;

procedure TfrmMain.ErrBox(stOut: string);
begin
  Application.MessageBox(PChar(stOut),'�������', mb_IconHand + mb_Ok);
end;

procedure TfrmMain.WrnBox(stOut: string);
begin
  Application.MessageBox(PChar(stOut),'�����', mb_IconWarning + mb_Ok);
end;

procedure TfrmMain.InfBox(stOut: string);
begin
  Application.MessageBox(PChar(stOut),'I���������', mb_IconAsterisk + mb_Ok);
end;

procedure TfrmMain.Terminal(stT: string);
begin
  memTerminal.Lines.Append(stT);
end;

// �������������� ����� � ������ � �������� ������ �����
function TfrmMain.Int2Str(wValue: word; bDigits: byte): string;
begin
  Result := IntToStr(wValue);
  while Length(Result) < bDigits do
    Result := '0' + Result;
end;

function TfrmMain.Time(Time: TDateTime): string;
var
  Hour,Min,Sec,MSec:    word;
begin
  DecodeTime(Time, Hour,Min,Sec,MSec);
  Result := Int2Str(Hour,2) + '.' +
            Int2Str(Min, 2)  + '.' +
            Int2Str(Sec, 2)  + '.' +
            Int2Str(MSec,3);
end;

procedure TfrmMain.Ready(wComNumber: word; Count: word);
begin
  datNow := Now;

  if wNumber <> wComNumber then begin
    Terminal('\\ COM' + IntToStr(wNumber)    + ':   ' + Time(datStop - datStart) +
             '   COM' + IntToStr(wNumber)    +
             '->COM'  + IntToStr(wComNumber) + ':   ' + Time(datNow - datStop));
    datStart := datNow;
  end;

  datStop := datNow;
  wNumber := wComNumber;

  Terminal('');
  Terminal('\\ COM' + IntToStr(wComNumber) + '    ' + Time(datNow));
end;

procedure TfrmMain.Dump(Count: word);
var
  i:    word;
  s,z:  string;
begin
  s := '';
  z := '';
  for i := 0 to Count - 1 do begin
    s := s + IntToHex(mpbInBuff[i],2) + ' ';
    if (mpbInBuff[i] < $20) then z := z + '_' else z := z + Chr(mpbInBuff[i]);
  end;

  s := s + '   \\ ' + IntToStr(Count) + ' ����: ' {+ z};
  Terminal(s);
end;

procedure TfrmMain.Comm1TriggerAvail(CP: TObject; Count: Word);
var
  p1,p2:  byte;
begin
  if Count > 0 then begin
    p2 := Random(100);
    if not(Timer1.Enabled) and (updProbability2.Position > 0) and (p2 < updProbability2.Position) then begin
      Timer1.Interval := UpDown1.Position;
      Timer1.Enabled := True;
      Caption := 'X';
    end;
    if (Timer1.Enabled) then begin Terminal('������������� 2'); exit; end;


    Ready(Comm1.ComNumber,Count);

    Comm1.GetBlock(mpbInBuff, Count);

    p1 := Random(100);
    if (updProbability1.Position = 0) or (p1 > updProbability1.Position) then
      Comm2.PutBlock(mpbInBuff, Count)
    else
      Terminal('������������� 1,%: ' + IntToStr(p1) + ' ' + IntToStr(updProbability1.Position));

    Dump(Count);
  end;
end;

procedure TfrmMain.Comm2TriggerAvail(CP: TObject; Count: Word);
var
  p1,p2:  byte;
begin
  if Count > 0 then begin
    p2 := Random(100);
    if not(Timer1.Enabled) and (updProbability2.Position > 0) and (p2 < updProbability2.Position) then begin
      Timer1.Interval := UpDown1.Position;
      Timer1.Enabled := True;
      Caption := 'X';
    end;
    if (Timer1.Enabled) then begin Terminal('������������� 2'); exit; end;

    Ready(Comm2.ComNumber,Count);

    Comm2.GetBlock(mpbInBuff, Count);

    p1 := Random(100);
    if (updProbability1.Position = 0) or (p1 > updProbability1.Position) then
      Comm1.PutBlock(mpbInBuff, Count)
    else
      Terminal('������������� 1,%: ' + IntToStr(p1) + ' ' + IntToStr(updProbability1.Position));

    Dump(Count);
  end;
end;

procedure TfrmMain.cmbComm1Change(Sender: TObject);
begin
  SetComm1(cmbComm1.ItemIndex + 1);
end;

procedure TfrmMain.cmbComm2Change(Sender: TObject);
begin
  SetComm2(cmbComm2.ItemIndex + 1);
end;

procedure TfrmMain.cmbBaud1Change(Sender: TObject);
begin
  with cmbBaud1 do begin
    try
      SetBaud1( StrToInt(Items.Strings[ItemIndex]) );
    except
      ErrBox('������� ��� �������i ��������i ����� �');
    end;
  end;
end;

procedure TfrmMain.cmbBaud2Change(Sender: TObject);
begin
  with cmbBaud2 do begin
    try
      SetBaud2( StrToInt(Items.Strings[ItemIndex]) );
    except
      ErrBox('������� ��� �������i ��������i ����� �');
    end;
  end;
end;

procedure TfrmMain.memTerminalKeyPress(Sender: TObject; var Key: Char);
begin
  if spbLeft.Down then
    Comm1.PutChar(Key)
  else
    Comm2.PutChar(Key);

  Terminal(IntToHex(Ord(Key),2) + ' ');
end;

procedure TfrmMain.Buttons;
begin
  if spbLeft.Down then
    Terminal('\\ COM' + IntToStr(Comm1.ComNumber))
  else
    Terminal('\\ COM' + IntToStr(Comm2.ComNumber));
end;

procedure TfrmMain.spbLeftClick(Sender: TObject);
begin
  spbRight.Down := not spbLeft.Down;
  Buttons;
end;

procedure TfrmMain.spbRightClick(Sender: TObject);
begin
  spbLeft.Down := not spbRight.Down;
  Buttons;
end;

procedure TfrmMain.Timer1Timer(Sender: TObject);
begin
      Timer1.Enabled := False;
      Caption := 'OK';
end;

end.
