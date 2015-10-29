program project2manager;

uses
  Vcl.Forms,
  main in 'main.pas' {frmMain},
  device in 'device.pas' {frmDevice};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
