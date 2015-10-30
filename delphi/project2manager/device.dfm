object frmDevice: TfrmDevice
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
  ClientHeight = 178
  ClientWidth = 211
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 120
  TextHeight = 18
  object Label1: TLabel
    Left = 8
    Top = 19
    Width = 14
    Height = 18
    Caption = 'IP'
  end
  object Label2: TLabel
    Left = 8
    Top = 59
    Width = 57
    Height = 18
    Caption = 'Gateway'
  end
  object Label3: TLabel
    Left = 8
    Top = 99
    Width = 58
    Height = 18
    Caption = 'Netmask'
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 145
    Width = 75
    Height = 25
    Caption = 'Save'
    ModalResult = 1
    TabOrder = 0
  end
  object BitBtn2: TBitBtn
    Left = 110
    Top = 145
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object medIP: TMaskEdit
    Left = 72
    Top = 16
    Width = 121
    Height = 26
    TabOrder = 2
  end
  object medGateway: TMaskEdit
    Left = 72
    Top = 56
    Width = 121
    Height = 26
    TabOrder = 3
  end
  object medNetmask: TMaskEdit
    Left = 72
    Top = 96
    Width = 121
    Height = 26
    TabOrder = 4
  end
end
