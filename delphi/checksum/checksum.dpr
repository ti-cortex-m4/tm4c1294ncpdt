program checksum;

{$APPTYPE CONSOLE}

uses
  SysUtils, Classes, System.IOUtils;

var
  b: TBytes;
  i: longword;
  s: longword;
  j: longint;
  MARK: AnsiString = 'ImageSize    ';
begin
  try
    try
      if ParamCount <> 2 then raise Exception.Create('checksum.exe input_file output_file');

      b := TFile.ReadAllBytes(ParamStr(1));
      s := Length(b);
      Writeln('File size: ' + IntToStr(s) + 'd / ' + IntToHex(s,8) + 'h');

      TFile.WriteAllBytes(ParamStr(1) + '.bak', b);

      j := 1;
      for i := 0 to s-1 do begin
        if b[i] = Ord(MARK[j]) then begin
          Inc(j);
          if (j = Length(MARK)-4+1) then begin
            Writeln('Label found: ' + IntToStr(i) + 'd / ' + IntToHex(i,8) + 'h');

            b[i+1] := (s mod $10000) mod $100;
            b[i+2] := (s mod $10000) div $100;
            b[i+3] := (s div $10000) mod $100;
            b[i+4] := (s div $10000) div $100;

            TFile.WriteAllBytes(ParamStr(2), b);
            exit;
          end;
        end else begin
          j := 1;
        end;
      end;

      Writeln('Label not found');
    except
      on E: Exception do Writeln(E.Message);
    end;
  finally
  end;

end.
