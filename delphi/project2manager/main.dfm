object frmMain: TfrmMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1072
  ClientHeight = 315
  ClientWidth = 506
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
  object pgcMain: TPageControl
    Left = 0
    Top = 0
    Width = 506
    Height = 315
    ActivePage = tbsSettings
    Align = alClient
    TabOrder = 0
    object tbsSettings: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      object panSettingsRight: TPanel
        Left = 371
        Top = 0
        Width = 127
        Height = 282
        Align = alRight
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 0
        object btbSearch: TBitBtn
          Left = 16
          Top = 16
          Width = 96
          Height = 28
          Caption = #1055#1086#1080#1089#1082
          Default = True
          TabOrder = 0
          OnClick = btbSearchClick
        end
        object btbSettings: TBitBtn
          Left = 16
          Top = 56
          Width = 96
          Height = 28
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
          TabOrder = 1
          OnClick = btbSettingsClick
        end
      end
      object panSettingsClient: TPanel
        Left = 0
        Top = 0
        Width = 371
        Height = 282
        Align = alClient
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 1
        object stgSettings: TStringGrid
          Left = 0
          Top = 0
          Width = 371
          Height = 282
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
            31
            114
            187)
        end
      end
    end
    object tbsTerminal: TTabSheet
      Caption = #1058#1077#1088#1084#1080#1085#1072#1083
      ImageIndex = 1
      object memTerminal: TMemo
        Left = 0
        Top = 0
        Width = 498
        Height = 282
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
