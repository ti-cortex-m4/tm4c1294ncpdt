object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1072
  ClientHeight = 313
  ClientWidth = 447
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 18
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 447
    Height = 313
    ActivePage = tbsSettings
    Align = alClient
    TabOrder = 0
    object tbsSettings: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      object panSettingsRight: TPanel
        Left = 312
        Top = 0
        Width = 127
        Height = 280
        Align = alRight
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 0
        object btbSearch: TBitBtn
          Left = 16
          Top = 16
          Width = 96
          Height = 25
          Caption = #1055#1086#1080#1089#1082
          TabOrder = 0
          OnClick = btbSearchClick
        end
        object btbSettings: TBitBtn
          Left = 16
          Top = 56
          Width = 96
          Height = 25
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
          TabOrder = 1
          OnClick = btbSettingsClick
        end
      end
      object panSettingsClient: TPanel
        Left = 0
        Top = 0
        Width = 312
        Height = 280
        Align = alClient
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 1
        object stgSettings: TStringGrid
          Left = 0
          Top = 0
          Width = 312
          Height = 280
          Align = alClient
          BevelEdges = []
          BevelInner = bvNone
          BevelOuter = bvNone
          ColCount = 3
          FixedCols = 0
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
          TabOrder = 0
          ColWidths = (
            22
            101
            160)
        end
      end
    end
    object tbsTerminal: TTabSheet
      Caption = #1058#1077#1088#1084#1080#1085#1072#1083
      ImageIndex = 1
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 439
        Height = 280
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Lucida Console'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object IdUDPServer: TIdUDPServer
    OnStatus = IdUDPServerStatus
    Active = True
    BroadcastEnabled = True
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 65535
      end>
    DefaultPort = 65535
    OnBeforeBind = IdUDPServerBeforeBind
    OnAfterBind = IdUDPServerAfterBind
    OnUDPRead = IdUDPServerUDPRead
    OnUDPException = IdUDPServerUDPException
    Left = 32
    Top = 104
  end
end
