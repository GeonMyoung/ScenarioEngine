#include <dz1_task_gen.h>
#include "code_template.h"
#include "code_gen_env_util.h"
#include "txt_replace_env_util.h"

#ifdef UNIX_SYSTEM
#pragma GCC diagnostic ignored "-Wformat-truncation" // modified by gm 20230602
#endif
static bool_t _utf8_flush(FILE *fp, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Str text = NULL;
	size_t utf8_sz = 0;
	u8_t *utf8 = NULL, utf8_bom[] = { 0xEF, 0xBB, 0xBF };
	if ((text = Dz1ElasticBuf_flattenStr(elb, errp)) == NULL) ERR_OUT(errp);
	else if ((utf8 = Dz1String_conv(text, Dz1STRLEN(text) * sizeof(TCHAR), DZ1_SYSTEM_CHARSET, "UTF-8", &utf8_sz)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if (fwrite(utf8_bom, sizeof(u8_t), sizeof(utf8_bom), fp) != sizeof(utf8_bom)) ERR_SET_OUT(errp, EPIPE);
		else if (fwrite(utf8, sizeof(u8_t), utf8_sz, fp) != utf8_sz) ERR_SET_OUT(errp, EPIPE);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// BASIC SETTING
#define VS2022_BASIC_SETTING_SINGLE(str_conf_name, str_platform) \
Dz1T("    <ProjectConfiguration Include=\"") Dz1T(str_conf_name) Dz1T("|") Dz1T(str_platform) Dz1T("\">"),\
Dz1T("      <Configuration>") Dz1T(str_conf_name) Dz1T("</Configuration>"),\
Dz1T("      <Platform>") Dz1T(str_platform) Dz1T("</Platform>"),\
Dz1T("    </ProjectConfiguration>")

#define VS2022_BASIC_SETTING \
Dz1T("  <ItemGroup Label=\"ProjectConfigurations\">"),\
		  VS2022_BASIC_SETTING_SINGLE("Debug", "Win32"),\
		  VS2022_BASIC_SETTING_SINGLE("Debug", "x64"),\
		  VS2022_BASIC_SETTING_SINGLE("Release", "Win32"),\
		  VS2022_BASIC_SETTING_SINGLE("Release", "x64"),\
Dz1T("  </ItemGroup>")
// BASIC SETTING
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GLOBAL SETUP
#define VS2022_GLOBAL_SETUP(sym_proj_guid, sym_proj_name) \
Dz1T("  <PropertyGroup Label=\"Globals\">"),\
Dz1T("    <VCProjectVersion>16.0</VCProjectVersion>"),\
Dz1T("    <Keyword>Win32Proj</Keyword>"),\
Dz1T("    <ProjectGuid>[[") #sym_proj_guid Dz1T("]]</ProjectGuid>"),\
Dz1T("    <RootNamespace>[[") #sym_proj_name Dz1T("]]</RootNamespace>"),\
Dz1T("    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>"),\
Dz1T("  </PropertyGroup>"),\
Dz1T("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />")
// GLOBAL SETUP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFIGURAION
#define VS2022_PROJ_TYPE_LIB		"StaticLibrary"
#define VS2022_PROJ_TYPE_CONSOLE	"Application"

#define VS2022_USE_MFC_STATIC		"Static"
#define VS2022_USE_MFC_DLL			"Dynamic"

#define VS2022_BASIC_CONFIGURATION_SINGLE(str_conf_name, str_platform, str_proj_type, str_use_mfc) \
Dz1T("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='") Dz1T(str_conf_name) Dz1T("|") Dz1T(str_platform) Dz1T("'\" Label=\"Configuration\">"),\
Dz1T("    <ConfigurationType>") Dz1T(str_proj_type) Dz1T("</ConfigurationType>"),\
Dz1T("    <UseDebugLibraries>true</UseDebugLibraries>"),\
Dz1T("    <PlatformToolset>v143</PlatformToolset>"),\
Dz1T("    <CharacterSet>MultiByte</CharacterSet>"),\
Dz1T("    <UseOfMfc>") Dz1T(str_use_mfc) Dz1T("</UseOfMfc>"),\
Dz1T("  </PropertyGroup>")

#define VS2022_BASIC_CONFIGURATION(str_proj_type, str_use_mfc) \
		VS2022_BASIC_CONFIGURATION_SINGLE("Debug", "Win32", str_proj_type, str_use_mfc),\
		VS2022_BASIC_CONFIGURATION_SINGLE("Debug", "x64", str_proj_type, str_use_mfc),\
		VS2022_BASIC_CONFIGURATION_SINGLE("Release", "Win32", str_proj_type, str_use_mfc),\
		VS2022_BASIC_CONFIGURATION_SINGLE("Release", "x64", str_proj_type, str_use_mfc),\
		Dz1T("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />"),\
		Dz1T("  <ImportGroup Label=\"ExtensionSettings\">"),\
		Dz1T("  </ImportGroup>")
// CONFIGURAION
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Output Path
#define VS2022_OUTOUT_PATH_SINGLE32(str_conf_name, str_platform, str_output_suffix) \
Dz1T("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='") Dz1T(str_conf_name) Dz1T("|") Dz1T(str_platform) Dz1T("'\">"),\
Dz1T("    <OutDir>$(Configuration)") Dz1T(str_output_suffix) Dz1T("\\</OutDir>"),\
Dz1T("    <IntDir>$(Configuration)") Dz1T(str_output_suffix) Dz1T("\\</IntDir>"),\
Dz1T("  </PropertyGroup>")

#define VS2022_OUTOUT_PATH_SINGLE64(str_conf_name, str_platform, str_output_suffix) \
Dz1T("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='") Dz1T(str_conf_name) Dz1T("|") Dz1T(str_platform) Dz1T("'\">"),\
Dz1T("    <OutDir>$(Configuration)") Dz1T(str_output_suffix) Dz1T("$(PlatformArchitecture)\\</OutDir>"),\
Dz1T("    <IntDir>$(Configuration)") Dz1T(str_output_suffix) Dz1T("$(PlatformArchitecture)\\</IntDir>"),\
Dz1T("  </PropertyGroup>")

#define VS2022_OUTOUT_PATH(str_output_suffix) \
		VS2022_OUTOUT_PATH_SINGLE32("Debug", "Win32", str_output_suffix),\
		VS2022_OUTOUT_PATH_SINGLE32("Release", "Win32", str_output_suffix),\
		VS2022_OUTOUT_PATH_SINGLE64("Debug", "x64", str_output_suffix),\
		VS2022_OUTOUT_PATH_SINGLE64("Release", "x64", str_output_suffix)
// Output Path
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Imports
#define VS2022_IMPORTS \
Dz1T("  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"PropertySheets\">"),\
Dz1T("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"),\
Dz1T("  </ImportGroup>"),\
Dz1T("  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"PropertySheets\">"),\
Dz1T("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"),\
Dz1T("  </ImportGroup>"),\
Dz1T("  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"PropertySheets\">"),\
Dz1T("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"),\
Dz1T("  </ImportGroup>"),\
Dz1T("  <ImportGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"PropertySheets\">"),\
Dz1T("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"),\
Dz1T("  </ImportGroup>")

#define VS2022_IMPORTS_FINAL \
Dz1T("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />"),\
Dz1T("  <ImportGroup Label=\"ExtensionTargets\">"),\
Dz1T("  </ImportGroup>")
// Imports
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Compile Parts
#define VS2022_COMPILE_DEFINE(str_type_define, str_define_build, str_wordsize) \
Dz1T("      <PreprocessorDefinitions>%(PreprocessorDefinitions);WIN32;") Dz1T(str_type_define) Dz1T(";__CLEANUP_C;__WORDSIZE=") Dz1T(str_wordsize) Dz1T(";__SYSTEM_ENDIAN_LITTLE__;") Dz1T(str_define_build) Dz1T("</PreprocessorDefinitions>")

#define VS2022_COMPILE_INCLUDE \
Dz1T("      <AdditionalIncludeDirectories>[[PROJ_INCLUDES]];[[PTHREAD_ROOT]];%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>")

#define VS2022_COMPILE_HEAD \
Dz1T("    <ClCompile>"),\
Dz1T("      <WarningLevel>Level3</WarningLevel>"),\
Dz1T("      <FunctionLevelLinking>false</FunctionLevelLinking>"),\
Dz1T("      <IntrinsicFunctions>false</IntrinsicFunctions>"),\
Dz1T("      <SDLCheck>true</SDLCheck>")

#define VS2022_COMPILE_BODY \
Dz1T("      <ConformanceMode>true</ConformanceMode>"),\
Dz1T("      <PrecompiledHeader>NotUsing</PrecompiledHeader>"),\
Dz1T("      <PrecompiledHeaderFile>stdafx.h</PrecompiledHeaderFile>")
// Compile Parts
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Compile Setting
#define VS2022_COMPILE_DEBUG(str_type_define, str_wordsize) \
VS2022_COMPILE_HEAD,\
VS2022_COMPILE_DEFINE(str_type_define, "_DEBUG", str_wordsize),\
VS2022_COMPILE_BODY,\
VS2022_COMPILE_INCLUDE,\
Dz1T("      <DebugInformationFormat>OldStyle</DebugInformationFormat>"),\
Dz1T("      <StringPooling>true</StringPooling>"),\
Dz1T("      <FunctionLevelLinking>false</FunctionLevelLinking>"),\
Dz1T("    </ClCompile>")

#define VS2022_COMPILE_RELEASE(str_type_define, str_wordsize) \
VS2022_COMPILE_HEAD \
VS2022_COMPILE_DEFINE(str_type_define, "NDEBUG", str_wordsize),\
VS2022_COMPILE_BODY,\
VS2022_COMPILE_INCLUDE,\
Dz1T("      <DebugInformationFormat>None</DebugInformationFormat>"),\
Dz1T("      <InlineFunctionExpansion>OnlyExplicitInline</InlineFunctionExpansion>"),\
Dz1T("      <StringPooling>true</StringPooling>"),\
Dz1T("    </ClCompile>")
// Compile Setting
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Link or AR Setting
#define VS2022_LINK_DEBUG \
Dz1T("    <Link>"),\
Dz1T("      <SubSystem>"),\
Dz1T("      </SubSystem>"),\
Dz1T("      <GenerateDebugInformation>true</GenerateDebugInformation>"),\
Dz1T("    </Link>")

#define VS2022_LINK_RELEASE \
Dz1T("    <Link>"),\
Dz1T("      <SubSystem>"),\
Dz1T("      </SubSystem>"),\
Dz1T("      <EnableCOMDATFolding>true</EnableCOMDATFolding>"),\
Dz1T("      <OptimizeReferences>true</OptimizeReferences>"),\
Dz1T("      <GenerateDebugInformation>true</GenerateDebugInformation>"),\
Dz1T("    </Link>")
// Link or AR Setting
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC File Helper
#define VS2022_FILE_INC_TDC_SPEC(sym_build_cfg, sym_platform) \
Dz1T("      <Command Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">[[DIMZ_TOOLS_PATH]]\\tdc.exe -I [[PROJ_INCLUDES]] -s ..\\..\\src ..\\..\\include\\%(Filename).tdc</Command>"),\
Dz1T("      <Message Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">TDC Compile for %(Filename).tdc</Message>"),\
Dz1T("      <Outputs Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">..\\..\\include\\%(Filename).h;..\\..\\src\\%(Filename).c;..\\..\\include\\%(Filename).tdo</Outputs>")

#define VS2022_FILE_INC_TDC(str_filename) \
Dz1T("    <CustomBuild Include=\"..\\..\\include\\[[") str_filename Dz1T("]].tdc\">"),\
Dz1T("      <FileType>Document</FileType>"),\
			VS2022_FILE_INC_TDC_SPEC(Debug, Win32),\
			VS2022_FILE_INC_TDC_SPEC(Release, Win32),\
			VS2022_FILE_INC_TDC_SPEC(Debug, x64),\
			VS2022_FILE_INC_TDC_SPEC(Release, x64),\
Dz1T("    </CustomBuild>")

#define VS2022_FILE_SRC_TDC_SPEC(sym_build_cfg, sym_platform) \
Dz1T("      <Command Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">[[DIMZ_TOOLS_PATH]]\\tdc.exe -I ..\\..\\src;[[PROJ_INCLUDES]] ..\\..\\src\\%(Filename).tdc</Command>"),\
Dz1T("      <Message Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">TDC Compile for %(Filename).tdc</Message>"),\
Dz1T("      <Outputs Condition=\"'$(Configuration)|$(Platform)'=='") #sym_build_cfg Dz1T("|") #sym_platform Dz1T("'\">..\\..\\src\\%(Filename).h;..\\..\\src\\%(Filename).c;..\\..\\src\\%(Filename).tdo</Outputs>")

#define VS2022_FILE_SRC_TDC(str_filename) \
Dz1T("    <CustomBuild Include=\"..\\..\\src\\[[") str_filename Dz1T("]].tdc\">"),\
Dz1T("      <FileType>Document</FileType>"),\
			VS2022_FILE_SRC_TDC_SPEC(Debug, Win32),\
			VS2022_FILE_SRC_TDC_SPEC(Release, Win32),\
			VS2022_FILE_SRC_TDC_SPEC(Debug, x64),\
			VS2022_FILE_SRC_TDC_SPEC(Release, x64),\
Dz1T("    </CustomBuild>")
// TDC File Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Task File Setting
#define VS2022_TASK_SRCS \
Dz1T("  <ItemGroup>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TDC_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_ARG_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_ENV_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TMR_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_MSGS_NAME]].c\" />"),\
Dz1T("  </ItemGroup>")

#define VS2022_TASK_HDRS \
Dz1T("  <ItemGroup>"),\
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_TDC_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_ARG_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_ENV_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_TMR_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_MSG_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_MSGS_NAME]].h\" />"),\
Dz1T("  </ItemGroup>")

#define VS2022_TASK_TDCS \
Dz1T("  <ItemGroup>"),\
		  VS2022_FILE_INC_TDC("PROJ_TDC_NAME"),\
		  VS2022_FILE_SRC_TDC("PROJ_ARG_NAME"),\
		  VS2022_FILE_SRC_TDC("PROJ_ENV_NAME"),\
		  VS2022_FILE_SRC_TDC("PROJ_TMR_NAME"),\
		  VS2022_FILE_SRC_TDC("PROJ_MSGS_NAME"),\
Dz1T("  </ItemGroup>")
// Task File Setting
///////////////////////////////////////////////////////////////////////////////

static Dz1Error __vs2022_proj_reference(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	Dz1ElasticBuf *elb = (Dz1ElasticBuf *)arg->dst;
	GenArgs2VisualStudioEntry *vs = GenArgs2VisualStudioList_getProj(p->projects, GenArgs2VisualStudioVer_vs2022);
	if (vs == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TCHAR toPath[2049], relPath[2048], rel_fn[2048];
		if ((*errp = Dz1PathStr_concat(toPath, 2048, p->path_root_abs, vs->middle_path, NULL)).code) ERR_OUT(errp);
		else if (_get_relative_path(relPath, 2048, arg->bias_path_abs, toPath, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = Dz1PathStr_concat(rel_fn, 2048, relPath, vs->proj_file_name, NULL)).code) ERR_OUT(errp);
		else
		{
			TCHAR str1[128] = { 0, }, str2[128] = { 0, };
			Dz1SNPRINTF(str1, 128, Dz1T("    <ProjectReference Include=\"%s\">\r\n"), rel_fn);
			Dz1SNPRINTF(str2, 128, Dz1T("      <Project>%s</Project>\r\n"), vs->proj_guid);

			if (Dz1ElasticBuf_pushStr(elb, str1, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1ElasticBuf_pushStr(elb, str2, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1ElasticBuf_pushStr(elb, Dz1T("    </ProjectReference>\r\n"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static bool_t _vs2022_proj_reference(Dz1ElasticBuf *elb, GenArgs2LibraryRefIndex *libs, Dz1Str vcproj_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (libs != NULL && libs->count(libs) > 0)
	{
		TextEmitArg arg = { elb, vcproj_path_abs, 0 };
		if (0) { }
		else if (Dz1ElasticBuf_pushStr(elb, Dz1T("  <ItemGroup>\r\n"), errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = libs->travel(libs, __vs2022_proj_reference, (void *)&arg)).code) ERR_OUT(errp);
		else if (Dz1ElasticBuf_pushStr(elb, Dz1T("  </ItemGroup>\r\n"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _vs2022_proj(FILE *fp, GenArgs2LibraryEntry *proj, GenArgs2LibraryRefIndex *libs, 
						   Dz1Str *head_template, Dz1Str *tail_template, TxtReplaceEnv *rp_env, 
						   Dz1GenTextMode txt_mode, Dz1Str proj_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBuf *elb = NULL;
	if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (TxtReplaceEnv_doElb(rp_env, elb, head_template, txt_mode, errp) == FALSE) ERR_OUT(errp);		// front
		else if (_vs2022_proj_reference(elb, libs, proj_path_abs, errp) == FALSE) ERR_OUT(errp);			// reference
		else if (TxtReplaceEnv_doElb(rp_env, elb, tail_template, txt_mode, errp) == FALSE) ERR_OUT(errp);	// rear
		else if (_utf8_flush(fp, elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Task Project Template
static Dz1Str vs2022_task_proj_head[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
VS2022_BASIC_SETTING,
NULL
};

static Dz1Str vs2022_task_proj_tail[] = {
VS2022_GLOBAL_SETUP(PROJ_TARGET_GUID, PROJ_NAME),
VS2022_BASIC_CONFIGURATION(VS2022_PROJ_TYPE_LIB, VS2022_USE_MFC_STATIC),
VS2022_OUTOUT_PATH(""),
VS2022_IMPORTS,
Dz1T("  <PropertyGroup Label=\"UserMacros\" />"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"),
VS2022_COMPILE_DEBUG("_LIB", "32"),
VS2022_LINK_DEBUG,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"),
VS2022_COMPILE_DEBUG("_LIB", "64"),
VS2022_LINK_DEBUG,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"),
VS2022_COMPILE_RELEASE("_LIB", "32"),
VS2022_LINK_RELEASE,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"),
VS2022_COMPILE_RELEASE("_LIB", "64"),
VS2022_LINK_RELEASE,
Dz1T("  </ItemDefinitionGroup>"),
VS2022_TASK_SRCS,
VS2022_TASK_HDRS,
VS2022_TASK_TDCS,
VS2022_IMPORTS_FINAL,
Dz1T("</Project>"),
NULL
};
// Task Project Template
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_task_proj(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->target) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_proj(fp, proj, env->libs, vs2022_task_proj_head, vs2022_task_proj_tail, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

#define VS2022_TEST_SRCS \


///////////////////////////////////////////////////////////////////////////////
// Library File Setting
#define VS2022_LIB_SRCS \
Dz1T("  <ItemGroup>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_NAME]].c\" />"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TDC_NAME]].c\" />"),\
Dz1T("  </ItemGroup>")

#define VS2022_LIB_HDRS \
Dz1T("  <ItemGroup>"),\
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_NAME]].h\" />"),\
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_TDC_NAME]].h\" />"),\
Dz1T("  </ItemGroup>")

#define VS2022_LIB_TDCS \
Dz1T("  <ItemGroup>"),\
		  VS2022_FILE_INC_TDC("PROJ_TDC_NAME"),\
Dz1T("  </ItemGroup>")
// Library File Setting
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Library Project Template
static Dz1Str vs2022_lib_proj_head[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
VS2022_BASIC_SETTING,
NULL
};

static Dz1Str vs2022_lib_proj_tail[] = {
VS2022_GLOBAL_SETUP(PROJ_TARGET_GUID, PROJ_NAME),
VS2022_BASIC_CONFIGURATION(VS2022_PROJ_TYPE_LIB, VS2022_USE_MFC_STATIC),
VS2022_OUTOUT_PATH(""),
VS2022_IMPORTS,
Dz1T("  <PropertyGroup Label=\"UserMacros\" />"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"),
VS2022_COMPILE_DEBUG("_LIB", "32"),
VS2022_LINK_DEBUG,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"),
VS2022_COMPILE_DEBUG("_LIB", "64"),
VS2022_LINK_DEBUG,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"),
VS2022_COMPILE_RELEASE("_LIB", "32"),
VS2022_LINK_RELEASE,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"),
VS2022_COMPILE_RELEASE("_LIB", "64"),
VS2022_LINK_RELEASE,
Dz1T("  </ItemDefinitionGroup>"),
VS2022_LIB_SRCS,
VS2022_LIB_HDRS,
VS2022_LIB_TDCS,
VS2022_IMPORTS_FINAL,
Dz1T("</Project>"),
NULL
};
// Library Project Template
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_lib_proj(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->target) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_proj(fp, proj, env->libs, vs2022_lib_proj_head, vs2022_lib_proj_tail, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Test Project Template
static Dz1Str vs2022_test_proj_head[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
VS2022_BASIC_SETTING,
NULL
};

#define VS2022_POST_BUILD_EVENT32 \
Dz1T("    <PostBuildEvent>"),\
Dz1T("      <Command>copy [[PTHREAD_ROOT]]\\project\\vs2022\\$(Configuration)\\pthreadVC2.dll $(IntDir)</Command>"),\
Dz1T("    </PostBuildEvent>")

#define VS2022_POST_BUILD_EVENT64 \
Dz1T("    <PostBuildEvent>"),\
Dz1T("      <Command>copy [[PTHREAD_ROOT]]\\project\\vs2022\\$(Configuration)$(PlatformArchitecture)\\pthreadVC2.dll $(IntDir)</Command>"),\
Dz1T("    </PostBuildEvent>")

#define VS2022_LINK_EXE_DEBUG \
Dz1T("    <Link>"),\
Dz1T("      <SubSystem>Console</SubSystem>"),\
Dz1T("      <GenerateDebugInformation>true</GenerateDebugInformation>"),\
Dz1T("    </Link>")

#define VS2022_LINK_EXE_RELEASE \
Dz1T("    <Link>"),\
Dz1T("      <SubSystem>Console</SubSystem>"),\
Dz1T("      <EnableCOMDATFolding>true</EnableCOMDATFolding>"),\
Dz1T("      <OptimizeReferences>true</OptimizeReferences>"),\
Dz1T("      <GenerateDebugInformation>true</GenerateDebugInformation>"),\
Dz1T("    </Link>")

static Dz1Str vs2022_test_proj_tail[] = {
VS2022_GLOBAL_SETUP(PROJ_TEST_GUID, PROJ_TEST_NAME),
VS2022_BASIC_CONFIGURATION(VS2022_PROJ_TYPE_CONSOLE, VS2022_USE_MFC_STATIC),
VS2022_OUTOUT_PATH("Test"),
VS2022_IMPORTS,
Dz1T("  <PropertyGroup Label=\"UserMacros\" />"),

Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"),
VS2022_COMPILE_DEBUG("_CONSOLE", "32"),
VS2022_LINK_EXE_DEBUG,
VS2022_POST_BUILD_EVENT32,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"),
VS2022_COMPILE_DEBUG("_CONSOLE", "64"),
VS2022_LINK_EXE_DEBUG,
VS2022_POST_BUILD_EVENT64,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"),
VS2022_COMPILE_RELEASE("_CONSOLE", "32"),
VS2022_LINK_EXE_RELEASE,
VS2022_POST_BUILD_EVENT32,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"),
VS2022_COMPILE_RELEASE("_CONSOLE", "64"),
VS2022_LINK_EXE_RELEASE,
VS2022_POST_BUILD_EVENT64,
Dz1T("  </ItemDefinitionGroup>"),
Dz1T("  <ItemGroup>"),
Dz1T("    <ClCompile Include=\"..\\..\\[[PROJ_TEST_NAME]].c\" />"),
Dz1T("  </ItemGroup>"),
VS2022_IMPORTS_FINAL,
Dz1T("</Project>"),
NULL
};
// Test Project Template
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_test_proj(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->test) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_proj(fp, proj, env->libs_test, vs2022_test_proj_head, vs2022_test_proj_tail, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Filter Basic
#define VS2022_FILTER_BASIC \
Dz1T("    <Filter Include=\"소스 파일\">"),\
Dz1T("      <UniqueIdentifier>[[$GUID]]</UniqueIdentifier>"),\
Dz1T("      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>"),\
Dz1T("    </Filter>"),\
Dz1T("    <Filter Include=\"헤더 파일\">"),\
Dz1T("      <UniqueIdentifier>[[$GUID]]</UniqueIdentifier>"),\
Dz1T("      <Extensions>h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd</Extensions>"),\
Dz1T("    </Filter>"),\
Dz1T("    <Filter Include=\"리소스 파일\">"),\
Dz1T("      <UniqueIdentifier>[[$GUID]]</UniqueIdentifier>"),\
Dz1T("      <Extensions>rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms</Extensions>"),\
Dz1T("    </Filter>")
// Filter Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter for Task
#define VS2022_FILTER_TASK \
Dz1T("    <Filter Include=\"소스 파일\\engine\">"),\
Dz1T("      <UniqueIdentifier>[[$GUID]]</UniqueIdentifier>"),\
Dz1T("    </Filter>"),\
Dz1T("    <Filter Include=\"소스 파일\\message\">"),\
Dz1T("      <UniqueIdentifier>[[$GUID]]</UniqueIdentifier>"),\
Dz1T("    </Filter>")
// Filter for Task
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter Source File Basic
#define VS2022_FILTER_SRC_FILE_BASIC \
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TDC_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일</Filter>"),\
Dz1T("    </ClCompile>")
// Filter Source File Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter Source File for TASK
#define VS2022_FILTER_SRC_FILE_TASK \
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_ARG_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_ENV_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TMR_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("    <ClCompile Include=\"..\\..\\src\\[[PROJ_MSGS_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일\\message</Filter>"),\
Dz1T("    </ClCompile>")
// Filter Source File for TASK
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter Header File Basic
#define VS2022_FILTER_HDR_FILE_BASIC \
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_NAME]].h\">"),\
Dz1T("      <Filter>헤더 파일</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\include\\[[PROJ_TDC_NAME]].h\">"),\
Dz1T("      <Filter>헤더 파일</Filter>"),\
Dz1T("    </ClInclude>")
// Filter Header File Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter Header File for TASK
#define VS2022_FILTER_HDR_FILE_TASK \
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_ARG_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_ENV_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_TMR_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_MSG_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\message</Filter>"),\
Dz1T("    </ClInclude>"),\
Dz1T("    <ClInclude Include=\"..\\..\\src\\[[PROJ_MSGS_NAME]].h\">"),\
Dz1T("      <Filter>소스 파일\\message</Filter>"),\
Dz1T("    </ClInclude>")
// Filter Header File for TASK
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter TDC File Basic
#define VS2022_FILTER_TDC_FILE_BASIC \
Dz1T("    <CustomBuild Include=\"..\\..\\include\\[[PROJ_TDC_NAME]].tdc\">"),\
Dz1T("      <Filter>헤더 파일</Filter>"),\
Dz1T("    </CustomBuild>")
// Filter TDC File Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filter TDC File for TASK
#define VS2022_FILTER_TDC_FILE_TASK \
Dz1T("    <CustomBuild Include=\"..\\..\\src\\[[PROJ_ARG_NAME]].tdc\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </CustomBuild>"),\
Dz1T("    <CustomBuild Include=\"..\\..\\src\\[[PROJ_ENV_NAME]].tdc\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </CustomBuild>"),\
Dz1T("    <CustomBuild Include=\"..\\..\\src\\[[PROJ_TMR_NAME]].tdc\">"),\
Dz1T("      <Filter>소스 파일\\engine</Filter>"),\
Dz1T("    </CustomBuild>"),\
Dz1T("    <CustomBuild Include=\"..\\..\\src\\[[PROJ_MSGS_NAME]].tdc\">"),\
Dz1T("      <Filter>소스 파일\\message</Filter>"),\
Dz1T("    </CustomBuild>")
// Filter TDC File for TASK
///////////////////////////////////////////////////////////////////////////////

static bool_t _vs2022_filters(FILE *fp, GenArgs2LibraryEntry *proj, Dz1Str *filters_template, TxtReplaceEnv *rp_env, Dz1GenTextMode txt_mode, Dz1Str proj_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBuf *elb = NULL;
	if ((elb = Dz1ElasticBuf_new(4096, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (TxtReplaceEnv_doElb(rp_env, elb, filters_template, txt_mode, errp) == FALSE) ERR_OUT(errp);
		else if (_utf8_flush(fp, elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// Filter for TASK
Dz1Str vs2022_task_proj_filters[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_BASIC,\
		  VS2022_FILTER_TASK,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_SRC_FILE_BASIC,\
		  VS2022_FILTER_SRC_FILE_TASK,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_HDR_FILE_BASIC,\
		  VS2022_FILTER_HDR_FILE_TASK,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_TDC_FILE_BASIC,\
		  VS2022_FILTER_TDC_FILE_TASK,\
Dz1T("  </ItemGroup>"),
Dz1T("</Project>"),
NULL
};
// Filter for TASK
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_task_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->target) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_filters(fp, proj, vs2022_task_proj_filters, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Filter for Lib
Dz1Str vs2022_lib_proj_filters[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_BASIC,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_SRC_FILE_BASIC,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_HDR_FILE_BASIC,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_TDC_FILE_BASIC,\
Dz1T("  </ItemGroup>"),
Dz1T("</Project>"),
NULL
};
// Filter for Lib
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_lib_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->target) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_filters(fp, proj, vs2022_lib_proj_filters, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Filter for Test
Dz1Str vs2022_test_proj_filters[] = {
Dz1T("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
Dz1T("<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"),
Dz1T("  <ItemGroup>"),
		  VS2022_FILTER_BASIC,\
Dz1T("  </ItemGroup>"),
Dz1T("  <ItemGroup>"),
Dz1T("    <ClCompile Include=\"..\\..\\[[PROJ_TEST_NAME]].c\">"),\
Dz1T("      <Filter>소스 파일</Filter>"),\
Dz1T("    </ClCompile>"),\
Dz1T("  </ItemGroup>"),
Dz1T("</Project>"),
NULL
};
// Filter for Test
///////////////////////////////////////////////////////////////////////////////

bool_t _vs2022_test_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryEntry *proj = NULL;
	GenArgs2VisualStudioEntry *vs2022 = NULL;
	if ((vs_env = env->vs_env) == NULL) ERR_SET_OUT(errp, EPERM);
	else if ((proj = vs_env->target) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_filters(fp, proj, vs2022_test_proj_filters, env->rp_env, env->txt_mode, work_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

/****************************************************************************************************************
*** Solution
*****************************************************************************************************************/

static Dz1Str vs2022_sln_head[] = {
Dz1T(""),
Dz1T("Microsoft Visual Studio Solution File, Format Version 12.00"),
Dz1T("# Visual Studio Version 17"),
Dz1T("VisualStudioVersion = 17.3.32804.467"),
Dz1T("MinimumVisualStudioVersion = 10.0.40219.1"),
NULL
};

/*
Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"Vs2022Lib\", \"Vs2022Lib.vcxproj\", \"{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}\""),
Dz1T("EndProject"),
Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"Vs2022Console\", \"Vs2022Console.vcxproj\", \"{48BA0A90-B666-48E1-A16E-E2CC93954FC3}\""),
Dz1T("EndProject"),
Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"pthread\", \"..\\..\\..\\pthreads.2\\project\\vs2022\\pthread.vcxproj\", \"{3F968544-3D37-446C-967C-B9426F0F527A}\""),
Dz1T("EndProject"),
Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"codeconv\", \"..\\..\\..\\codeconv\\project\\vs2022\\codeconv.vcxproj\", \"{9B4AB3EF-8C73-4BBF-8176-9E00AC6FCCC3}\""),
Dz1T("EndProject"),
Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"dz1\", \"..\\..\\..\\dimz\\dz1\\project\\vs2022\\dz1.vcxproj\", \"{78EDEE71-C212-4C81-9AFF-02F055137471}\""),
Dz1T("EndProject"),
*/

static bool_t _vs2022_sln_project(Dz1ElasticBuf *elb, GenArgs2LibraryEntry *proj, Dz1Str sln_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2VisualStudioEntry *vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022);
	if (vs2022 == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TCHAR proj_path_abs[512] = { 0, }, proj_relative_path[512] = { 0, }, proj_relative_fn[512] = { 0, };
		if ((*errp = Dz1PathStr_concat(proj_path_abs, 512, proj->path_root_abs, vs2022->middle_path, NULL)).code) ERR_OUT(errp);
		else if (_get_relative_path(proj_relative_path, 512, sln_path_abs, proj_path_abs, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = Dz1PathStr_concat(proj_relative_fn, 512, proj_relative_path, vs2022->proj_file_name, NULL)).code) ERR_OUT(errp);
		else
		{
			TCHAR str[1024];
			Dz1SNPRINTF(str, 1024, Dz1T("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"%s\", \"%s\", \"%s\"\r\n"), proj->name, proj_relative_fn, vs2022->proj_guid);
			if (Dz1ElasticBuf_pushStr(elb, str, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1ElasticBuf_pushStr(elb, Dz1T("EndProject\r\n"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error _sln_lib_project(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	Dz1ElasticBuf *elb = (Dz1ElasticBuf *)arg->dst;
	Dz1Str sln_path_abs = arg->bias_path_abs;

	if (_vs2022_sln_project(elb, p, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static bool_t _vs2022_sln_projects(Dz1ElasticBuf *elb, GenEnv *env, Dz1Str sln_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = env->vs_env;
	if (_vs2022_sln_project(elb, vs_env->target, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
	else if (vs_env->test != NULL && _vs2022_sln_project(elb, vs_env->test, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
	else
	{
		GenArgs2LibraryRefIndex *libs = env->libs;
		TextEmitArg arg = { elb, sln_path_abs, 0 };
		if ((*errp = libs->travel(libs, _sln_lib_project, (void *)&arg)).code) ERR_OUT(errp);
		else if (_vs2022_sln_project(elb, env->dimz_dz1, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_project(elb, env->codeconv, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_project(elb, vs_env->ptw_win, sln_path_abs, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Str vs2022_sln_mid[] = {
Dz1T("Global"),
Dz1T("	GlobalSection(SolutionConfigurationPlatforms) = preSolution"),
Dz1T("		Debug|x64 = Debug|x64"),
Dz1T("		Debug|Win32 = Debug|Win32"),
Dz1T("		Release|x64 = Release|x64"),
Dz1T("		Release|Win32 = Release|Win32"),
Dz1T("	EndGlobalSection"),
Dz1T("	GlobalSection(ProjectConfigurationPlatforms) = postSolution"),
NULL
};

/*
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Debug|x64.ActiveCfg = Debug|x64"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Debug|x64.Build.0 = Debug|x64"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Debug|Win32.ActiveCfg = Debug|Win32"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Debug|Win32.Build.0 = Debug|Win32"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Release|x64.ActiveCfg = Release|Win32"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Release|x64.Build.0 = Release|Win32"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Release|Win32.ActiveCfg = Release|Win32"),
Dz1T("		{2FEE56DC-EF6C-44C1-85E4-BC348B1BEA29}.Release|Win32.Build.0 = Release|Win32"),
*/

static bool_t _vs2022_sln_build_single(Dz1ElasticBuf *elb, GenArgs2VisualStudioEntry *vs2022, Dz1Str conf_name, Dz1Str platform_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR str1[128], str2[128];
	Dz1SNPRINTF(str1, 128, Dz1T("		%s.%s|%s.ActiveCfg = %s|%s\r\n"), vs2022->proj_guid, conf_name, platform_name, conf_name, platform_name);
	Dz1SNPRINTF(str2, 128, Dz1T("		%s.%s|%s.Build.0 = %s|%s\r\n"), vs2022->proj_guid, conf_name, platform_name, conf_name, platform_name);
	if (Dz1ElasticBuf_pushStr(elb, str1, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1ElasticBuf_pushStr(elb, str2, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _vs2022_sln_build_project(Dz1ElasticBuf *elb, GenArgs2LibraryEntry *proj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2VisualStudioEntry *vs2022 = GenArgs2VisualStudioList_getProj(proj->projects, GenArgs2VisualStudioVer_vs2022);
	if (vs2022 == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (_vs2022_sln_build_single(elb, vs2022, Dz1T("Debug"), Dz1T("Win32"), errp) == FALSE) ERR_OUT(errp);
	else if (_vs2022_sln_build_single(elb, vs2022, Dz1T("Debug"), Dz1T("x64"), errp) == FALSE) ERR_OUT(errp);
	else if (_vs2022_sln_build_single(elb, vs2022, Dz1T("Release"), Dz1T("Win32"), errp) == FALSE) ERR_OUT(errp);
	else if (_vs2022_sln_build_single(elb, vs2022, Dz1T("Release"), Dz1T("x64"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error _sln_lib_build(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	Dz1ElasticBuf *elb = (Dz1ElasticBuf *)arg->dst;

	if (_vs2022_sln_build_project(elb, p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static bool_t _vs2022_sln_build(Dz1ElasticBuf *elb, GenEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = env->vs_env;
	if (_vs2022_sln_build_project(elb, vs_env->target, errp) == FALSE) ERR_OUT(errp);
	else if (vs_env->test != NULL && _vs2022_sln_build_project(elb, vs_env->test, errp) == FALSE) ERR_OUT(errp);
	else
	{
		GenArgs2LibraryRefIndex *libs = env->libs;
		TextEmitArg arg = { elb, NULL, 0 };
		if ((*errp = libs->travel(libs, _sln_lib_build, (void *)&arg)).code) ERR_OUT(errp);
		else if (_vs2022_sln_build_project(elb, env->dimz_dz1, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_build_project(elb, env->codeconv, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_build_project(elb, vs_env->ptw_win, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Str vs2022_sln_tail[] = {
Dz1T("	EndGlobalSection"),
Dz1T("	GlobalSection(SolutionProperties) = preSolution"),
Dz1T("		HideSolutionNode = FALSE"),
Dz1T("	EndGlobalSection"),
Dz1T("	GlobalSection(ExtensibilityGlobals) = postSolution"),
Dz1T("		SolutionGuid = [[$GUID]]"),
Dz1T("	EndGlobalSection"),
Dz1T("EndGlobal"),
NULL
};

bool_t _vs2022_sln(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = Dz1ElasticBuf_new(4096, FALSE, errp);
	if (elb == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (TxtReplaceEnv_doElb(env->rp_env, elb, vs2022_sln_head, Dz1GenTextMode_DOS, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_projects(elb, env, work_path_abs, errp) == FALSE) ERR_OUT(errp);
		else if (TxtReplaceEnv_doElb(env->rp_env, elb, vs2022_sln_mid, Dz1GenTextMode_DOS, errp) == FALSE) ERR_OUT(errp);
		else if (_vs2022_sln_build(elb, env, errp) == FALSE) ERR_OUT(errp);
		else if (TxtReplaceEnv_doElb(env->rp_env, elb, vs2022_sln_tail, Dz1GenTextMode_DOS, errp) == FALSE) ERR_OUT(errp);
		else if (_utf8_flush(fp, elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
