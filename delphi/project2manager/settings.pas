unit settings;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons, Vcl.Mask,
  Vcl.ExtCtrls;

type
  TfrmSettings = class(TForm)
    panBottom: TPanel;
    panRight: TPanel;
    btbCancel: TBitBtn;
    btbSave: TBitBtn;
    panClient: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    medIP: TMaskEdit;
    medGateway: TMaskEdit;
    medNetmask: TMaskEdit;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmSettings: TfrmSettings;

implementation

{$R *.dfm}

end.
