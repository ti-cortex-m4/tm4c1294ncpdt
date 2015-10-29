object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'project2manager'
  ClientHeight = 333
  ClientWidth = 437
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 437
    Height = 333
    ActivePage = tbsSettings
    Align = alClient
    TabOrder = 0
    object tbsSettings: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      object panSettingsRight: TPanel
        Left = 324
        Top = 0
        Width = 105
        Height = 302
        Align = alRight
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 0
        object btbSearch: TBitBtn
          Left = 16
          Top = 16
          Width = 75
          Height = 25
          Caption = #1055#1086#1080#1089#1082
          TabOrder = 0
          OnClick = btbSearchClick
        end
      end
      object panSettingsClient: TPanel
        Left = 0
        Top = 0
        Width = 324
        Height = 302
        Align = alClient
        BevelEdges = []
        BevelOuter = bvNone
        TabOrder = 1
        object stgSettings: TStringGrid
          Left = 0
          Top = 0
          Width = 324
          Height = 302
          Align = alClient
          BevelEdges = []
          BevelInner = bvNone
          BevelOuter = bvNone
          ColCount = 3
          FixedCols = 0
          RowCount = 2
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
      object btbStartClient: TBitBtn
        Left = 8
        Top = 8
        Width = 80
        Height = 25
        Caption = 'start client'
        TabOrder = 0
        OnClick = btbStartClientClick
      end
      object btbStopClient: TBitBtn
        Left = 94
        Top = 8
        Width = 80
        Height = 25
        Caption = 'stop client'
        TabOrder = 1
        OnClick = btbStopClientClick
      end
      object btbStartServer: TBitBtn
        Left = 216
        Top = 8
        Width = 80
        Height = 25
        Caption = 'start server'
        TabOrder = 2
        OnClick = btbStartServerClick
      end
      object btbStopServer: TBitBtn
        Left = 302
        Top = 8
        Width = 80
        Height = 25
        Caption = 'stop server'
        TabOrder = 3
        OnClick = btbStopServerClick
      end
      object Memo1: TMemo
        Left = 8
        Top = 39
        Width = 644
        Height = 290
        TabOrder = 4
      end
    end
  end
  object IdUDPClient: TIdUDPClient
    OnStatus = IdUDPClientStatus
    BroadcastEnabled = True
    Port = 0
    OnConnected = IdUDPClientConnected
    OnDisconnected = IdUDPClientDisconnected
    Left = 568
  end
  object IdUDPServer: TIdUDPServer
    OnStatus = IdUDPServerStatus
    BroadcastEnabled = True
    Bindings = <>
    DefaultPort = 0
    OnBeforeBind = IdUDPServerBeforeBind
    OnAfterBind = IdUDPServerAfterBind
    OnUDPRead = IdUDPServerUDPRead
    OnUDPException = IdUDPServerUDPException
    Left = 616
  end
end
