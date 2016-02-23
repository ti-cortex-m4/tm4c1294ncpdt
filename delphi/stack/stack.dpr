program stack;

{$APPTYPE CONSOLE}

uses
  SysUtils, Classes;

var
  Source: TStringList;
  Target1: TStringList;
  Target2: TStringList;

  i,j,b,e: word;
  s,z: string;
  PrevName, PrevAddr: string;
  CurrName, CurrAddr: string;
  Align: byte;

  State: (INIT, FIRST, NEXT, LAST);

function PackStrR(stT: string; wSize: word): string;
begin
  Result := stT;
  while Length(Result) < wSize do Result := Result + ' ';
end;

begin
  try
    Source := TStringList.Create;
    Target1 := TStringList.Create;
    Target2 := TStringList.Create;

    try
      if ParamCount < 4 then raise Exception.Create('stack.exe input_file output_file1 output_file2 align');

      Align := StrToInt(ParamStr(4));
      State := INIT;

      Source.Loadfromfile(ParamStr(1));

      for i := 1 to Source.Count do begin
        s := Source.Strings[i-1];

        b := Pos('BEGIN(',s);
        e := LastDelimiter(')',s);
        if (b > 0) and (e > 0) and (b < e) then begin
          z := Copy(s, b+6, e-b-6);
          j := Pos(',', z);
          if (j > 0) then begin
            PrevName := Trim(Copy(z, 1, j-1));
            PrevAddr := Trim(Copy(z, j+1, Length(z)-j));

            Target1.Add('  ' + PackStrR(PrevName, Align) + ' = ' + PrevAddr + ',');
            Target2.Add('  PUSH_VALUE(' + PrevName + ')');

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

              Target1.Add('  ' + PackStrR(CurrName, Align) + ' = ' + PrevName + ',');
              Target2.Add('  PUSH_ADDRESS(' + CurrName + ')');
            end
            else begin
              Target1.Add('  ' + PackStrR(CurrName, Align) + ' = ' + PrevName + ' + ' + PrevAddr + ',');
              Target2.Add('  PUSH_ADDRESS(' + CurrName + ')');
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

          Target1.Add('  ' + PackStrR(CurrName, Align) + ' = ' + PrevName + ' + ' + PrevAddr);
          Target2.Add('  PUSH_VALUE(' + CurrName + ')');

          State := LAST;
          continue;
        end;

        Target1.Add(s);
        if (s = '') then Target2.Add(s);
      end;

      Target1.SaveToFile(ParamStr(2));
      Target2.SaveToFile(ParamStr(3));
    except
      on E: Exception do Writeln(E.Message);
    end;
  finally
    if (Source <> nil) then Source.Free;
    if (Target1 <> nil) then Target1.Free;
    if (Target2 <> nil) then Target2.Free;
  end;

end.
