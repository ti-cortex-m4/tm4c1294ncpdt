�
 TFRMMAIN 0a  TPF0TfrmMainfrmMainLeft/Top	Width�Height�Caption!   Аналiзатар трафiкаColor	clBtnFaceFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style OldCreateOrder	PositionpoScreenCenterOnClose	FormCloseOnResize
FormResizeOnShowFormShowPixelsPerInchx
TextHeight TPanel	panClientLeft Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrder  TPageControlpgcMainLeft Top Width�Height
ActivePagetbsSettingsAlignalClientTabOrder  	TTabSheettbsTerminalCaption   Тэрмiнал TMemomemTerminalLeft Top WidthfHeight;AlignalClientFont.CharsetRUSSIAN_CHARSET
Font.ColorclGrayFont.Height�	Font.NameLucida Console
Font.Style 
ParentFontReadOnly	
ScrollBars
ssVerticalTabOrder 
OnKeyPressmemTerminalKeyPress   	TTabSheettbsSettingsCaption   0;04K
ImageIndex TLabellblFlashDayToLeft
TopWidth� HeightCaption   Выпадковасьць 1,%  TLabelLabel1Left
Top4Width� HeightCaption   Выпадковасьць 2,%  TLabelLabel2Left
TopZWidth� HeightCaption   Выпадковасьць 3,%  TEditedtFlashDayMaxLeft� Top
Width'HeightTabOrder Text0  TUpDownupdProbability1Left� Top
WidthHeight	AssociateedtFlashDayMaxTabOrder	Thousands  TEditEdit1Left� Top0Width'HeightTabOrderText0  TUpDownupdProbability2Left� Top0WidthHeight	AssociateEdit1TabOrder	Thousands  TEditEdit2Left� TopVWidth'HeightTabOrderText0  TUpDownupdProbability3Left� TopVWidthHeight	AssociateEdit2TabOrder	Thousands  TEditEdit3Left
Top0Width'HeightTabOrderText500  TUpDownUpDown1Left1Top0WidthHeight	AssociateEdit3Max�Position�TabOrder	Thousands     TPanel	panBottomLeft TopWidth�Height_AlignalBottom
BevelOuterbvNoneTabOrder TPanelpanLeftLeft Top Width�Height_AlignalLeftTabOrder  TLabellblComm1LeftTopWidth5HeightCaption   Порт А  TLabellblBaud1Left� TopWidthIHeightCaption	   %CB:0ALFL  TSpeedButtonspbLeftLeft� Top0WidthHeight
AllowAllUp	
GroupIndexOnClickspbLeftClick  	TComboBoxcmbComm1LeftTop0Width_HeightStylecsDropDownListDropDownCount
ItemHeightTabOrder OnChangecmbComm1ChangeItems.StringsCOM1COM2COM3COM4COM5COM6COM7COM8   	TComboBoxcmbBaud1Left� Top0Width_HeightStylecsDropDownListDropDownCount
ItemHeightTabOrderOnChangecmbBaud1ChangeItems.Strings1103006001200240048009600192003840057600115200    TPanelpanRightLeft�Top WidthBHeight_AlignalClientTabOrder TLabellblComm2LeftTopWidth3HeightCaption   Порт В  TLabellblBaud2Left� TopWidthIHeightCaption	   %CB:0ALFL  TSpeedButtonspbRightLeft� Top0WidthHeight
AllowAllUp	
GroupIndexDown	OnClickspbRightClick  	TComboBoxcmbComm2LeftTop0Width_HeightStylecsDropDownListDropDownCount
ItemHeightTabOrder OnChangecmbComm2ChangeItems.StringsCOM1COM2COM3COM4COM5COM6COM7COM8   	TComboBoxcmbBaud2Left� Top0Width_HeightStylecsDropDownListDropDownCount
ItemHeightTabOrderOnChangecmbBaud2ChangeItems.Strings1103006001200240048009600192003840057600115200     TApdComPortComm1	ComNumberBaud�%InSize  TracingtlOn	TraceSize0u	TraceName	comm1.trcLoggingtlOnLogSizeP�  LogName	comm1.logOnTriggerAvailComm1TriggerAvailLeft� Top(  TApdComPortComm2	ComNumberBaud�%InSize  TracingtlOn	TraceSize0u	TraceName	comm2.trcLoggingtlOnLogSizeP�  LogName	comm2.logOnTriggerAvailComm2TriggerAvailLeft� Top(  TTimerTimer1EnabledInterval�OnTimerTimer1TimerLeft$Top+   