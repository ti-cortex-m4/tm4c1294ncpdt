object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'project2manager'
  ClientHeight = 396
  ClientWidth = 723
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object btbStartClient: TBitBtn
    Left = 8
    Top = 8
    Width = 80
    Height = 25
    Caption = 'start client'
    TabOrder = 0
    OnClick = btbStartClientClick
  end
  object Memo1: TMemo
    Left = 8
    Top = 39
    Width = 707
    Height = 349
    TabOrder = 1
  end
  object btbStopClient: TBitBtn
    Left = 94
    Top = 8
    Width = 80
    Height = 25
    Caption = 'stop client'
    TabOrder = 2
    OnClick = btbStopClientClick
  end
  object btbStartServer: TBitBtn
    Left = 216
    Top = 8
    Width = 80
    Height = 25
    Caption = 'start server'
    TabOrder = 3
    OnClick = btbStartServerClick
  end
  object btbStopServer: TBitBtn
    Left = 302
    Top = 8
    Width = 80
    Height = 25
    Caption = 'stop server'
    TabOrder = 4
    OnClick = btbStopServerClick
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
