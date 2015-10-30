program project2manager;

uses
  Vcl.Forms,
  main in 'main.pas' {frmMain},
  settings in 'settings.pas' {frmSettings};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
