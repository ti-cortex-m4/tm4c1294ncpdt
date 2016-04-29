unit fifo;

interface

uses SysUtils, AdPort, Generics.Collections;

type
  TItem = class
  public
    FComPort: TApdComPort;
    FData: TBytes;
    constructor Create(const AComPort: TApdComPort; const AData: TBytes);
    destructor Destroy; override;
  end;

function ToBytes(mbBuff: array of byte; Size: word): TBytes;

implementation

constructor TItem.Create(const AComPort: TApdComPort; const AData: TBytes);
begin
  FComPort := AComPort;
  FData := AData;
end;

destructor TItem.Destroy;
begin
  SetLength(FData, 0);
  inherited;
end;

function ToBytes(mbBuff: array of byte; Size: word): TBytes;
var
  i: word;
begin
  SetLength(Result, Size);
  for i := 0 to Size-1 do begin
    Result[i] := mbBuff[i];
  end;
end;

end.

