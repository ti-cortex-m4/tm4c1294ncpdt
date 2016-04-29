program traffic5;

uses
  Forms,
  main in 'main.pas' {frmMain},
  support in 'support.pas',
  fifo in 'fifo.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'COM-COM траффик';
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
