# Unit Test - French

The following files are used for unit testing the conversion from integer to French words.


# File generation

The test files were generated from Microsoft Word 2010 using the French language pack.

To convert a number to words, enter the following commands:

1) Hit `CTRL+F9` key. The following field will be added to the document `{ }`.
2) Enter the following command within the brackets: `=<number> \*CardText` replacing `<number>` by the actual integer value to convert. For examples, to convert the number 34 to words, enter `=34 \*CardText`.
3) Hit `CTRL+F9` key again to convert the code to actual text.


# Source code

The following Visual Basic for Application (VBA) code converts all integer values from 0 to 999999 and saves the results to files in `C:\temp` folder.

```vbnet
Sub RunCustomLoop()
    On Error GoTo ErrorHandler
    Title = "User response required"
    loopStart = InputBox("Please enter the first value", Title, "0")
    loopStart = Int(loopStart)
    loopEnd = InputBox("Please enter the last value", Title, "100")
    loopEnd = Int(loopEnd)
    
    PrintNumbers loopStart, loopEnd

ErrorHandler:
End Sub

Sub RunAutomaticLoops()
    'PrintNumbers 0, 9999
    'PrintNumbers 10000, 19999
    'etc
    For i = 0 To 99
        loopStart = i * 10000
        loopEnd = ((i + 1) * 10000) - 1
        PrintNumbers loopStart, loopEnd
    Next
End Sub

Private Sub PrintNumbers(ByVal loopStart As Long, ByVal loopEnd As Long)
    NewDocument
    
    'Add custom field for each value
    For i = loopStart To loopEnd
        'Create an empty special field
        Selection.Fields.Add Range:=Selection.Range, Type:=wdFieldEmpty, PreserveFormatting:=False
        
        'Type the function to print a number as text
        Selection.TypeText Text:="=" & i & " \*CardText"
        
        If (i <> loopEnd) Then
            'Position carret to the next line
            Selection.EndKey Unit:=wdLine
            Selection.TypeParagraph
        End If
    Next
    
    'Convert codes to actual text
    UpdateAllFields
    
    'Define output filename
    Dim filename
    filename = "Nombres_" & Format(loopStart, "000000") & "_to_" & Format(loopEnd, "000000") & ".txt"
    
    'Save document as *.txt file
    ChangeFileOpenDirectory "C:\Temp\"
    ActiveDocument.SaveAs2 filename:=filename, FileFormat:=wdFormatText, _
        LockComments:=False, Password:="", AddToRecentFiles:=True, WritePassword _
        :="", ReadOnlyRecommended:=False, EmbedTrueTypeFonts:=False, _
        SaveNativePictureFormat:=False, SaveFormsData:=False, SaveAsAOCELetter:= _
        False, Encoding:=1252, InsertLineBreaks:=False, AllowSubstitutions:=False _
        , LineEnding:=wdCRLF, CompatibilityMode:=0
        
    'Close document
    ActiveDocument.Close
End Sub

Private Sub NewDocument()
Attribute NewDocument.VB_ProcData.VB_Invoke_Func = "Project.NewMacros.a"
    Dim doc As Document
    Set doc = Documents.Add(DocumentType:=wdNewBlankDocument)
    doc.Activate
    
    'Select ALL
    Selection.WholeStory
    
    'Delete content
    Selection.Delete Unit:=wdCharacter, Count:=1
    
    'Set paragraph settings
    With Selection.ParagraphFormat
        .LeftIndent = InchesToPoints(0)
        .RightIndent = InchesToPoints(0)
        .SpaceBefore = 0
        .SpaceBeforeAuto = False
        .SpaceAfter = 0
        .SpaceAfterAuto = False
        .LineSpacingRule = wdLineSpaceMultiple
        .LineSpacing = LinesToPoints(1#)
        .Alignment = wdAlignParagraphLeft
        .WidowControl = True
        .KeepWithNext = False
        .KeepTogether = False
        .PageBreakBefore = False
        .NoLineNumber = False
        .Hyphenation = True
        .FirstLineIndent = InchesToPoints(0)
        .OutlineLevel = wdOutlineLevelBodyText
        .CharacterUnitLeftIndent = 0
        .CharacterUnitRightIndent = 0
        .CharacterUnitFirstLineIndent = 0
        .LineUnitBefore = 0
        .LineUnitAfter = 0
        .MirrorIndents = False
        .TextboxTightWrap = wdTightNone
        .CollapsedByDefault = False
    End With
    
    'Set FRENCH language
    Selection.LanguageID = wdFrench
    Selection.NoProofing = False
    Application.CheckLanguage = True
End Sub

Private Sub UpdateAllFields()
    'Select ALL
    Selection.WholeStory
    
    'Toggle fields code
    Selection.Fields.Update
End Sub
```