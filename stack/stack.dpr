program stack;

{$APPTYPE CONSOLE}

uses
  SysUtils, Classes;

var
  SourceList: TStringList;
  TargetList: TStringList;

  i,j,b,e: word;
  s,z: string;
  PrevName, PrevAddr: string;
  CurrName, CurrAddr: string;

  State: (INIT, FIRST, NEXT, LAST);

function PackStrR(stT: string; wSize: word): string;
begin
  Result := stT;
  while Length(Result) < wSize do Result := Result + ' ';
end;

begin
  try
    SourceList := TStringList.Create;
    TargetList := TStringList.Create;

    try
      if ParamCount < 2 then raise Exception.Create('stack.exe input_file output_file');
      State := INIT;

      SourceList.Loadfromfile(ParamStr(1));

      for i := 1 to SourceList.Count do begin
        s := SourceList.Strings[i-1];

        b := Pos('BEGIN(',s);
        e := LastDelimiter(')',s);
        if (b > 0) and (e > 0) and (b < e) then begin
          z := Copy(s, b+6, e-b-6);
          j := Pos(',', z);
          if (j > 0) then begin
            PrevName := Trim(Copy(z, 1, j-1));
            PrevAddr := Trim(Copy(z, j+1, Length(z)-j));

            TargetList.Add('  ' + PackStrR(PrevName, 21) + ' = ' + PrevAddr + ',');
            State := FIRST;

            continue;
          end;
        end;

        b := Pos('RESERVE(',s);
        e := LastDelimiter(')',s);
        if (b > 0) and (e > 0) and (b < e) then begin
          z := Copy(s, b+8, e-b-8);
          j := Pos(',', z);
          if (j > 0) then begin
            CurrName := Trim(Copy(z, 1, j-1));
            CurrAddr := Trim(Copy(z, j+1, Length(z)-j));

            if (State = FIRST) then begin
              State := NEXT;
              TargetList.Add('  ' + PackStrR(CurrName, 21) + ' = ' + PrevName + ',');
            end
            else begin
              TargetList.Add('  ' + PackStrR(CurrName, 21) + ' = ' + PrevName + ' + ' + PrevAddr + ',');
            end;

            PrevName := CurrName;
            PrevAddr := CurrAddr;
          end;

          continue;
        end;

        b := Pos('END(',s);
        e := LastDelimiter(')',s);
        if (b > 0) and (e > 0) and (b < e) then begin
          z := Trim(Copy(s, b+4, e-b-4));
          CurrName := z;

          TargetList.Add('  ' + PackStrR(CurrName, 21) + ' = ' + PrevName + ' + ' + PrevAddr);
          State := LAST;

          continue;
        end;

        TargetList.Add(s);
      end;

      TargetList.SaveToFile(ParamStr(2));
    except
      on E: Exception do Writeln(E.Message);
    end;
  finally
    if (SourceList <> nil) then SourceList.Free;
    if (TargetList <> nil) then TargetList.Free;
  end;

end.
