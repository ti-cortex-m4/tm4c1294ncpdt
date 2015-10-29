unit device;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Buttons, Vcl.Mask;

type
  TfrmDevice = class(TForm)
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    medIP: TMaskEdit;
    medGateway: TMaskEdit;
    medNetmask: TMaskEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmDevice: TfrmDevice;

implementation

{$R *.dfm}

end.
