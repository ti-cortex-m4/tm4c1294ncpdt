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
  object BitBtn1: TBitBtn
    Left = 8
    Top = 8
    Width = 80
    Height = 25
    Caption = 'start client'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 39
    Width = 707
    Height = 349
    TabOrder = 1
  end
  object BitBtn2: TBitBtn
    Left = 94
    Top = 8
    Width = 80
    Height = 25
    Caption = 'stop client'
    TabOrder = 2
    OnClick = BitBtn2Click
  end
  object BitBtn3: TBitBtn
    Left = 216
    Top = 8
    Width = 80
    Height = 25
    Caption = 'start server'
    TabOrder = 3
    OnClick = BitBtn3Click
  end
  object BitBtn4: TBitBtn
    Left = 302
    Top = 8
    Width = 80
    Height = 25
    Caption = 'stop server'
    TabOrder = 4
    OnClick = BitBtn4Click
  end
  object IdUDPClient1: TIdUDPClient
    OnStatus = IdUDPClient1Status
    BroadcastEnabled = True
    Port = 0
    OnConnected = IdUDPClient1Connected
    OnDisconnected = IdUDPClient1Disconnected
    Left = 568
  end
  object IdUDPServer1: TIdUDPServer
    OnStatus = IdUDPServer1Status
    BroadcastEnabled = True
    Bindings = <>
    DefaultPort = 0
    OnBeforeBind = IdUDPServer1BeforeBind
    OnAfterBind = IdUDPServer1AfterBind
    OnUDPRead = IdUDPServer1UDPRead
    OnUDPException = IdUDPServer1UDPException
    Left = 616
  end
end
