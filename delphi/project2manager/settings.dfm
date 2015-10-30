object frmSettings: TfrmSettings
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 184
  ClientWidth = 299
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
  object panBottom: TPanel
    Left = 0
    Top = 143
    Width = 299
    Height = 41
    Align = alBottom
    BevelEdges = []
    TabOrder = 0
    object panRight: TPanel
      Left = 81
      Top = 1
      Width = 217
      Height = 39
      Align = alRight
      BevelEdges = []
      BevelOuter = bvNone
      TabOrder = 0
      object btbCancel: TBitBtn
        Left = 118
        Top = 6
        Width = 88
        Height = 28
        Caption = #1054#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 1
      end
      object btbSave: TBitBtn
        Left = 16
        Top = 6
        Width = 88
        Height = 28
        Caption = #1047#1072#1087#1080#1089#1072#1090#1100
        Default = True
        ModalResult = 1
        TabOrder = 0
      end
    end
  end
  object panClient: TPanel
    Left = 0
    Top = 0
    Width = 299
    Height = 143
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 19
      Width = 14
      Height = 18
      Caption = 'IP'
    end
    object Label2: TLabel
      Left = 24
      Top = 59
      Width = 76
      Height = 18
      Caption = 'Gateway IP'
    end
    object Label3: TLabel
      Left = 24
      Top = 99
      Width = 85
      Height = 18
      Caption = 'Subnet mask'
    end
    object medIP: TMaskEdit
      Left = 119
      Top = 15
      Width = 120
      Height = 26
      TabOrder = 0
    end
    object medGateway: TMaskEdit
      Left = 119
      Top = 56
      Width = 120
      Height = 26
      TabOrder = 1
    end
    object medNetmask: TMaskEdit
      Left = 119
      Top = 96
      Width = 120
      Height = 26
      TabOrder = 2
    end
  end
end
