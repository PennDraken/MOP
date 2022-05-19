##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=snake
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP
ProjectPath            :=C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=henry
Date                   :=19/05/2022
CodeLitePath           :=C:/cseapp/CodeLite
LinkerName             :=$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="snake.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostdlib -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc 
ArLibs                 :=  "gcc" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-ar.exe rcu
CXX      := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
CC       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc.exe
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\cseapp\CodeLite
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=$(IntermediateDirectory)/geometries.c$(ObjectSuffix) $(IntermediateDirectory)/counting_circuits.c$(ObjectSuffix) $(IntermediateDirectory)/ascii_display.c$(ObjectSuffix) $(IntermediateDirectory)/game.c$(ObjectSuffix) $(IntermediateDirectory)/keypad.c$(ObjectSuffix) $(IntermediateDirectory)/init.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	C:\cseapp\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  Debug/snake Debug/snake.s19
	C:\cseapp\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S Debug/snake > Debug/snake.lst
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/geometries.c$(ObjectSuffix): geometries.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/geometries.c$(ObjectSuffix) -MF$(IntermediateDirectory)/geometries.c$(DependSuffix) -MM geometries.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/geometries.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/geometries.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/geometries.c$(PreprocessSuffix): geometries.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/geometries.c$(PreprocessSuffix) geometries.c

$(IntermediateDirectory)/counting_circuits.c$(ObjectSuffix): counting_circuits.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/counting_circuits.c$(ObjectSuffix) -MF$(IntermediateDirectory)/counting_circuits.c$(DependSuffix) -MM counting_circuits.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/counting_circuits.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/counting_circuits.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/counting_circuits.c$(PreprocessSuffix): counting_circuits.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/counting_circuits.c$(PreprocessSuffix) counting_circuits.c

$(IntermediateDirectory)/ascii_display.c$(ObjectSuffix): ascii_display.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ascii_display.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ascii_display.c$(DependSuffix) -MM ascii_display.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/ascii_display.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ascii_display.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ascii_display.c$(PreprocessSuffix): ascii_display.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ascii_display.c$(PreprocessSuffix) ascii_display.c

$(IntermediateDirectory)/game.c$(ObjectSuffix): game.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/game.c$(ObjectSuffix) -MF$(IntermediateDirectory)/game.c$(DependSuffix) -MM game.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/game.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/game.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/game.c$(PreprocessSuffix): game.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/game.c$(PreprocessSuffix) game.c

$(IntermediateDirectory)/keypad.c$(ObjectSuffix): keypad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keypad.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keypad.c$(DependSuffix) -MM keypad.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/keypad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keypad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keypad.c$(PreprocessSuffix): keypad.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keypad.c$(PreprocessSuffix) keypad.c

$(IntermediateDirectory)/init.c$(ObjectSuffix): init.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/init.c$(ObjectSuffix) -MF$(IntermediateDirectory)/init.c$(DependSuffix) -MM init.c
	$(CC) $(SourceSwitch) "C:/Users/henry/OneDrive/Skrivbord/VT21/MOP/MOP/MOP/snake/init.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/init.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/init.c$(PreprocessSuffix): init.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/init.c$(PreprocessSuffix) init.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


