unit support;

interface

uses Classes;

function Int2Str(wT: word; bSize: byte = 2): string;

function PackLine(wSize: word): string;
function PackStrR(stT: string; wSize: word): string;
function PackStrL(stT: string; wSize: word): string;

function DateTime2Str: string;

function FromBCD(bT: byte): byte;
function ToBCD(bT: byte): byte;

procedure ErrBox(stT: string);
procedure WrnBox(stT: string);
procedure InfBox(stT: string);

implementation

uses Windows, Forms, SysUtils, Graphics;//, main, output, get_config;

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

function DateTime2Str: string;
begin
  Result := FormatDateTime('hh.mm.ss dd.mm.yyyy',Now);
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
  Application.MessageBox(PChar(stT + ' '), 'Ошибка', mb_Ok + mb_IconHand);
end;

procedure WrnBox(stT: string);
begin
  Application.MessageBox(PChar(stT + ' '), 'Внимание', mb_Ok + mb_IconWarning);
end;

procedure InfBox(stT: string);
begin
  Application.MessageBox(PChar(stT + ' '), 'Информация', mb_Ok + mb_IconAsterisk);
end;

end.
