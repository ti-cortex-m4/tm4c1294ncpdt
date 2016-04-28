unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, OoMisc, AdPort, IniFiles, Buttons;

type
  TfrmMain = class(TForm)
    panClient: TPanel;
    panBottom: TPanel;
    Comm1: TApdComPort;
    Comm2: TApdComPort;
    pgcMain: TPageControl;
    tbsTerminal: TTabSheet;
    memTerminal: TMemo;
    lblComm1: TLabel;
    cmbComm1: TComboBox;
    cmbBaud1: TComboBox;
    cmbComm2: TComboBox;
    cmbBaud2: TComboBox;
    lblComm2: TLabel;
    panRigth2: TPanel;
    btbCrealInfo: TBitBtn;
    btbSaveInfo: TBitBtn;
    sd_RichToFile: TSaveDialog;
    tbsSettings: TTabSheet;
    lblDelay: TLabel;
    edtDelay: TEdit;
    updDelay: TUpDown;
    edtDelayDispersion: TEdit;
    updDelayDispersion: TUpDown;
    lblDelayDispersion: TLabel;
    procedure FormResize(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SetBaud1(dwBaud: longint);
    procedure SetComm1(wComNumber: word);
    procedure SetBaud2(dwBaud: longint);
    procedure SetComm2(wComNumber: word);
    procedure Terminal(stT: string);
    procedure Ready(wComNumber: word; Count: word);
    procedure Dump(Count: word);
    procedure Comm1TriggerAvail(CP: TObject; Count: Word);
    procedure Comm2TriggerAvail(CP: TObject; Count: Word);
    procedure cmbComm1Change(Sender: TObject);
    procedure cmbComm2Change(Sender: TObject);
    procedure cmbBaud1Change(Sender: TObject);
    procedure cmbBaud2Change(Sender: TObject);
    procedure SaveMemo(Memo: TMemo; stName: string);
    procedure btbSaveInfoClick(Sender: TObject);
    procedure btbCrealInfoClick(Sender: TObject);
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
  datStop:              TDateTime;
  wComNumberPrev:       word = 100;

const
  stCOMM1:              string  = 'Порт А';
  stCOMM2:              string  = 'Порт В';
  stCOMNUMBER:          string  = 'Нумар';
  stBAUD:               string  = 'Хуткасьць';
  stSETTINGS:           string  = 'Налады';
  sDELAY:               string  = 'Delay';
  sDELAY_DISPERSION:    string  = 'DelayDispersion';

  dwDEFAULT_BAUD:       longint = 9600;

implementation

uses support;

{$R *.DFM}

procedure TfrmMain.FormResize(Sender: TObject);
begin
  if Height < 200 then Height := 200;
  if Width  < 500 then Width  := 500;
end;

procedure TfrmMain.FormShow(Sender: TObject);
var
  stIni: string;
begin
  try
    stIni := ChangeFileExt(ParamStr(0),'.ini');
    FileSetAttr(stIni, FileGetAttr(stIni) and not faReadOnly);
  except
  end;

  try
    FIni := TIniFile.Create(ChangeFileExt(ParamStr(0),'.ini'));

    SetComm1( FIni.ReadInteger(stCOMM1, stCOMNUMBER, 1) );
    SetBaud1( FIni.ReadInteger(stCOMM1, stBAUD,      dwDEFAULT_BAUD) );

    SetComm2( FIni.ReadInteger(stCOMM2, stCOMNUMBER, 2) );
    SetBaud2( FIni.ReadInteger(stCOMM2, stBAUD,      dwDEFAULT_BAUD) );

    updDelay.Position := FIni.ReadInteger(stSETTINGS, sDELAY, 0);
    updDelayDispersion.Position := FIni.ReadInteger(stSETTINGS, sDELAY_DISPERSION, 0);
  except
    ErrBox('Памылка пры чытаньнi парамертаў');
  end;

  with Comm1 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('Памылковы нумар парта А: COM' + IntToStr(ComNumber));
      ComNumber := 1;
    end;
    cmbComm1.ItemIndex := ComNumber - 1;

    if cmbBaud1.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('Памылковая хуткасьць парта А: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud1.ItemIndex := cmbBaud1.Items.IndexOf( IntToStr(Baud) );
  end;

  with Comm2 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('Памылковы нумар парта В: COM' + IntToStr(ComNumber));
      ComNumber := 2;
    end;
    cmbComm2.ItemIndex := ComNumber - 1;

    if cmbBaud2.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('Памылковая хуткасьць парта В: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud2.ItemIndex := cmbBaud2.Items.IndexOf( IntToStr(Baud) );
  end;
  
  Comm1.Open := True;
  Comm2.Open := True;

  datStart := Now;
  datStop  := Now;

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

    FIni.WriteInteger(stSETTINGS, sDELAY, updDelay.Position);
    FIni.WriteInteger(stSETTINGS, sDELAY_DISPERSION, updDelayDispersion.Position);
  except
    ErrBox('Памылка пры запiсваньнi парамертаў');
  end;
end;

procedure TfrmMain.SetComm1(wComNumber: word);
begin
  with Comm1 do begin
    try
      ComNumber := wComNumber;
    except
      ComNumber := 1;
      ErrBox('Памылка пры змяненьнi нумара парта А: COM' + IntToStr(wComNumber));
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
      ErrBox('Памылка пры змяненьнi хуткасьцi парта А: ' + IntToStr(dwBaud));
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
      ErrBox('Памылка пры змяненьнi нумара парта В: COM' + IntToStr(wComNumber));
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
      ErrBox('Памылка пры змяненьнi хуткасьцi парта В: ' + IntToStr(dwBaud));
    end;
  end;
end;

procedure TfrmMain.Terminal(stT: string);
begin
  memTerminal.Lines.Append(stT);
end;

procedure TfrmMain.Ready(wComNumber: word; Count: word);
var
  datNow: TDateTime;
begin
  datNow := Now;

  if (wComNumberPrev <> wComNumber) and (wComNumberPrev <> 100) then begin
    Terminal('');
    Terminal('\\ COM' + IntToStr(wComNumberPrev) + ':  ' + Time2Str(datStop - datStart) +
             '   COM' + IntToStr(wComNumberPrev) +
             '->COM'  + IntToStr(wComNumber) + ':  ' + Time2Str(datNow - datStop));
    datStart := datNow;
  end;

  if (wComNumberPrev <> wComNumber) then begin
    Terminal('');
    Terminal('\\ COM' + IntToStr(wComNumber));
  end;

  datStop := datNow;
  wComNumberPrev := wComNumber;
end;

procedure TfrmMain.Dump(Count: word);
var
  i: word;
  s: string;
begin
  s := '';
  for i := 0 to Count - 1 do begin
    s := s + IntToHex(mpbInBuff[i],2) + ' ';
  end;

  s := s + '   \\ ' + IntToStr(Count) + ' байт:  ' + Time2Str(Now);
  Terminal(s);
end;

procedure Delay1;
var
  wDelay: word;
begin
  with frmMain do
  if updDelay.Position > 0 then begin
    wDelay := Round(updDelay.Position*(1 + (Random(updDelayDispersion.Position*2) - updDelayDispersion.Position)/100));
    Terminal('\\ задержка ' + IntToStr(wDelay) + ' мс.');
    Delay(wDelay);
  end;
end;

procedure TfrmMain.Comm1TriggerAvail(CP: TObject; Count: Word);
begin
  if Count > 0 then begin
    Ready(Comm1.ComNumber,Count);

    Comm1.GetBlock(mpbInBuff, Count);
    Delay1;
    Comm2.PutBlock(mpbInBuff, Count);

    Dump(Count);
  end;
end;

procedure TfrmMain.Comm2TriggerAvail(CP: TObject; Count: Word);
begin
  if Count > 0 then begin
    Ready(Comm2.ComNumber,Count);

    Comm2.GetBlock(mpbInBuff, Count);
    Delay1;
    Comm1.PutBlock(mpbInBuff, Count);

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
      ErrBox('Памылка пры заданьнi хуткасьцi парта А');
    end;
  end;
end;

procedure TfrmMain.cmbBaud2Change(Sender: TObject);
begin
  with cmbBaud2 do begin
    try
      SetBaud2( StrToInt(Items.Strings[ItemIndex]) );
    except
      ErrBox('Памылка пры заданьнi хуткасьцi парта В');
    end;
  end;
end;

procedure TfrmMain.SaveMemo(Memo: TMemo; stName: string);
begin
  with sd_RichToFile,Memo do begin
    try
      InitialDir := ExtractFileDir(ParamStr(0));

      ForceDirectories(InitialDir);
      FileName := stName + '.txt';

      if Execute then Memo.Lines.SaveToFile(FileName);
    except
      ErrBox('Ошибка при сохранении отчёта !')
    end;
  end;
end;

procedure TfrmMain.btbSaveInfoClick(Sender: TObject);
begin
  SaveMemo(memTerminal, 'Траффик ' + DateTime2Str(Now) + ' ');
end;

procedure TfrmMain.btbCrealInfoClick(Sender: TObject);
begin
  memTerminal.Clear;
end;

end.
