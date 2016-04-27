program traffic5;

uses
  Forms,
  main in 'main.pas' {frmMain};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := ' Аналiзатар трафiка ';
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
