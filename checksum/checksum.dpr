program checksum;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  Classes, System.IOUtils;

var
  b: TBytes;
  i: longword;

begin
  try
    try
      if ParamCount < 2 then raise Exception.Create('checksum.exe input_file output_file');

      b := TFile.ReadAllBytes(ParamStr(1));
      for i := 0 to Length(b) do begin
      end;
    except
      on E: Exception do Writeln(E.Message);
    end;
  finally
  end;

end.
