object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Chat :)'
  ClientHeight = 646
  ClientWidth = 845
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Icon.Data = {
    0000010001002020040000000000E80200001600000028000000200000004000
    0000010004000000000000020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000111111000000000000000000000000119999991000000000
    0000000000001199999999910000000000000000001199900099999900000000
    0111111111999100000999991000000019999999999000000009999990000001
    9999999999999999990099999000000999999999999999999990999990000009
    9999999999999999999901199000000999999999991000000999009990000000
    9999910000077770099009990000000019900077077777788099999900000000
    1100700707700007801999990000000000070070770000007809999000000000
    0000000000700000780999900000000000000700007000007809999000000000
    0000000000700000780999900000000000070070700000007809999000000000
    0007007070000000780999900000000000070070700000078809999000000000
    0007007070000007801999990000000000070007070000078099999900000000
    0000700707000078019999990000000000007000707777780999999900000000
    0000007700088880999999100000000000000000091000099999000000000000
    0000001991019999990000000000000000000000000999991000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFFFF03FFFFFC01FFFFF000FFFFC0007F8000007F0000003E0000003C000
    0003C0000003C0000003C0000003E0000007E0000007F061E007F8C3F00FFC61
    F00FFC21F00FFC61F00FFCC7F00FFCC7F00FFCC7E00FFCC7E007FCE3E007FE63
    C007FE700000FF00000FFF000017FF8000DBFFC003EDFFFE07F7FFFFFFFF}
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 607
    Height = 630
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    Visible = False
    object Memo2: TMemo
      Left = 8
      Top = 447
      Width = 587
      Height = 139
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      MaxLength = 256
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      WantReturns = False
    end
    object Memo1: TMemo
      Left = 8
      Top = 8
      Width = 587
      Height = 433
      TabStop = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object Panel4: TPanel
      Left = 8
      Top = 592
      Width = 587
      Height = 29
      BevelOuter = bvNone
      ParentBackground = False
      TabOrder = 2
      object Label7: TLabel
        Left = 0
        Top = 8
        Width = 229
        Height = 13
        Caption = 'Press Alt + underlined letter to fire the shortcut'
      end
      object Button6: TButton
        Left = 416
        Top = 0
        Width = 88
        Height = 25
        Caption = 'Save &History'
        TabOrder = 1
        OnClick = Button6Click
      end
      object Button5: TButton
        Left = 314
        Top = 0
        Width = 96
        Height = 25
        Caption = 'Set &Background'
        TabOrder = 3
        OnClick = Button5Click
      end
      object Button4: TButton
        Left = 233
        Top = 0
        Width = 75
        Height = 25
        Caption = 'Set &Font'
        TabOrder = 2
        OnClick = Button4Click
      end
      object Button1: TButton
        Left = 510
        Top = 0
        Width = 75
        Height = 25
        Caption = '&Send'
        TabOrder = 0
        OnClick = Button1Click
      end
    end
  end
  object Panel2: TPanel
    Left = 8
    Top = 8
    Width = 265
    Height = 161
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 59
      Width = 138
      Height = 13
      Caption = 'IPv4 remote server address:'
    end
    object Label2: TLabel
      Left = 24
      Top = 105
      Width = 24
      Height = 13
      Caption = 'Port:'
    end
    object Label3: TLabel
      Left = 24
      Top = 11
      Width = 50
      Height = 13
      Caption = 'NickName:'
    end
    object Edit1: TEdit
      Left = 24
      Top = 78
      Width = 225
      Height = 21
      TabOrder = 1
    end
    object Edit2: TEdit
      Left = 24
      Top = 124
      Width = 41
      Height = 21
      MaxLength = 5
      TabOrder = 2
    end
    object Button3: TButton
      Left = 71
      Top = 122
      Width = 178
      Height = 25
      Caption = '&Connect'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Edit3: TEdit
      Left = 24
      Top = 32
      Width = 225
      Height = 21
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 621
    Top = 8
    Width = 215
    Height = 629
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 2
    Visible = False
    object Label5: TLabel
      Left = 8
      Top = 33
      Width = 4
      Height = 18
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 11
      Width = 42
      Height = 16
      Caption = 'Roster:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object Panel5: TPanel
      Left = 0
      Top = 592
      Width = 209
      Height = 29
      BevelOuter = bvNone
      TabOrder = 0
      object Label6: TLabel
        Left = 16
        Top = 6
        Width = 101
        Height = 13
        Caption = 'Auto refresh in 5sec.'
      end
      object Button2: TButton
        Left = 123
        Top = 0
        Width = 75
        Height = 25
        Caption = '&Refresh'
        TabOrder = 0
        OnClick = Button2Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 5000
    OnTimer = Timer1Timer
    Left = 632
    Top = 568
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 664
    Top = 568
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    Filter = 'Text file|txt|All Files'
    Options = [ofHideReadOnly, ofPathMustExist, ofNoNetworkButton, ofEnableSizing]
    Title = 'Save Chat History'
    Encodings.Strings = (
      'ANSI'
      'ASCII'
      'Unicode'
      'Big Endian Unicode'
      'UTF-7'
      'UTF-8')
    EncodingIndex = 5
    Left = 728
    Top = 568
  end
  object ColorDialog1: TColorDialog
    Left = 696
    Top = 568
  end
end
