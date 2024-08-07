unit support;

interface

uses Classes;

function Int2Str(wT: word; bSize: byte = 2): string;

function PackLine(wSize: word): string;
function PackStrR(stT: string; wSize: word): string;
function PackStrL(stT: string; wSize: word): string;

function DateTime2Str(const DateTime: TDateTime): string;
function Time2Str(const DateTime: TDateTime): string;
function Buff2Str(const mbBuff: array of byte; const Count: word): string;

function FromBCD(bT: byte): byte;
function ToBCD(bT: byte): byte;

procedure ErrBox(stT: string);
procedure WrnBox(stT: string);
procedure InfBox(stT: string);

procedure Delay(MSec: longword);

implementation

uses Windows, Forms, SysUtils, Graphics;

function Int2Str(wT: word; bSize: byte = 2): string;
begin
  Result := IntToStr(wT);
  while Length(Result) < bSize do Result := '0' + Result;
end;

function PackLine(wSize: word): string;
begin
  Result := '';
  while Length(Result) < wSize do Result := Result + '-';
end;

function PackStrR(stT: string; wSize: word): string;
begin
  Result := stT;
  while Length(Result) < wSize do Result := Result + ' ';
end;

function PackStrL(stT: string; wSize: word): string;
begin
  Result := stT;
  while Length(Result) < wSize do Result := ' ' + Result;
end;

function DateTime2Str(const DateTime: TDateTime): string;
begin
  Result := FormatDateTime('hh.mm.ss dd.mm.yyyy',DateTime);
end;

function Time2Str(const DateTime: TDateTime): string;
begin
  Result := FormatDateTime('hh.mm.ss.zzz',DateTime);
end;

function Buff2Str(const mbBuff: array of byte; const Count: word): string;
var
  i: word;
begin
  Result := '';
  for i := 0 to Count - 1 do begin
    Result := Result + IntToHex(mbBuff[i],2) + ' ';
  end;

  Result := Result + '   \\ ' + IntToStr(Count) + ' ����:  ' + Time2Str(Now);
end;

function FromBCD(bT: byte): byte;
begin
  Result := (bT div 16)*10 + (bT mod 16);
end;

function ToBCD(bT: byte): byte;
begin
  Result := (bT div 10)*16 + bT mod 10;
end;

procedure ErrBox(stT: string);
begin
  Application.MessageBox(PChar(stT + ' '), '������', mb_Ok + mb_IconHand);
end;

procedure WrnBox(stT: string);
begin
  Application.MessageBox(PChar(stT + ' '), '��������', mb_Ok + mb_IconWarning);
end;

procedure InfBox(stT: string);
begin
  Application.MessageBox(PChar(stT + ' '), '����������', mb_Ok + mb_IconAsterisk);
end;

procedure Delay(MSec: longword);
var
  FirstTickCount,Now: longword;
begin
  FirstTickCount := GetTickCount;
  repeat
    Application.ProcessMessages;
    Now := GetTickCount;
  until (Now - FirstTickCount >= MSec) or (Now < FirstTickCount);
end;

end.
