///////////////////////////////////////////////////////////////////////////////
///
/// \file Configuration.cpp
/// Implementation of the Configuration Classes.
/// 
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Zero
{

namespace Events
{
DefineEvent(RecentProjectsUpdated);
}//namespace Events


//------------------------------------------------------------------ Main Config
bool MainConfig::sConfigCanSave = true;

ZilchDefineType(MainConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  ZilchBindFieldGetterProperty(ApplicationName);
  ZilchBindGetterProperty(BuildDate);
  ZilchBindGetterProperty(BuildVersion);
  type->AddAttribute(ObjectAttributes::cCore);
}

void MainConfig::Initialize(CogInitializer& initializer)
{
  mConfigDidNotExist = false;
  mSave = true;
  mLocallyBuilt = false;
}

String MainConfig::GetBuildDate()
{
  return GetChangeSetDateString();
}

String MainConfig::GetBuildVersion()
{
  return GetBuildVersionName();
}

void MainConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(ApplicationName, String());
}

//---------------------------------------------------------------- Editor Config
ZilchDefineType(EditorConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindSetup(SetupMode::DefaultSerialization);
  type->AddAttribute(ObjectAttributes::cCore);
  ZilchBindFieldProperty(ZeroHubUsername);
}

void EditorConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(EditingProject, String());
  SerializeNameDefault(EditingLevel, String());
  SerializeNameDefault(ZeroHubUsername, String());
}

//--------------------------------------------------------------- Content Config
ZilchDefineType(ContentConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  type->AddAttribute(ObjectAttributes::cCore);
}

void ContentConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(ContentOutput, String());
  SerializeNameDefault(ToolsDirectory, String());
  SerializeNameDefault(LibraryDirectories, LibraryDirectories);
  SerializeEnumNameDefault(Verbosity, ContentVerbosity, Verbosity::Minimal);
  SerializeNameDefault(HistoryEnabled, true);
}


//------------------------------------------------------------------ User Config
ZilchDefineType(UserConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindSetup(SetupMode::DefaultSerialization);
  ZilchBindFieldProperty(UserName);
  ZilchBindFieldProperty(UserEmail);
  type->AddAttribute(ObjectAttributes::cCore);
}

UserConfig::UserConfig()
  :LoggedIn(false)
{

}

void UserConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(UserName, String());
  SerializeNameDefault(UserEmail, String());
  SerializeNameDefault(Authentication, String());

  SerializeNameDefault(LastVersionKnown, 0u);
  SerializeNameDefault(LastVersionUsed, 0u);
  SerializeNameDefault(LastAcceptedEulaHash, (u64)0);
}

//------------------------------------------------------------- Developer Config
ZilchDefineType(DeveloperConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  ZilchBindFieldProperty(mDoubleEscapeQuit);
  ZilchBindFieldProperty(mProxyObjectsInPreviews);
  ZilchBindFieldProperty(mCanModifyReadOnlyResources);
}

DeveloperConfig::DeveloperConfig()
{
  // We don't want to serialize this because it could be dangerous
  mProxyObjectsInPreviews = true;
}

void DeveloperConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(mDoubleEscapeQuit, false);
  SerializeNameDefault(mCanModifyReadOnlyResources, false);
  SerializeNameDefault(mGenericFlags, HashSet<String>());
}

//------------------------------------------------------------------ ZilchPluginConfig
ZilchDefineType(ZilchPluginConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindDocumented();
  ZilchBindFieldProperty(mAttemptedIdeToolsInstall);
  type->AddAttribute(ObjectAttributes::cCore);
}

ZilchPluginConfig::ZilchPluginConfig()
{
  mAttemptedIdeToolsInstall = false;
}

void ZilchPluginConfig::Initialize(CogInitializer& initializer)
{
}

void ZilchPluginConfig::Serialize(Serializer& stream)
{
  SerializeNameDefault(mAttemptedIdeToolsInstall, false);
}

//----------------------------------------------------------- Text Editor Config
ZilchDefineType(TextEditorConfig, builder, type)
{
  ZeroBindComponent();
  ZeroBindSetup(SetupMode::DefaultSerialization);
  ZeroBindDocumented();
  ZilchBindFieldProperty(TabWidth);
  ZilchBindFieldProperty(ShowWhiteSpace);
  ZilchBindFieldProperty(LineNumbers);
  ZilchBindFieldProperty(CodeFolding);
  ZilchBindFieldProperty(TextMatchHighlighting);
  ZilchBindFieldProperty(HighlightPartialTextMatch);
  ZilchBindFieldProperty(ConfidentAutoCompleteOnSymbols);
  ZilchBindFieldProperty(LocalWordCompletion);
  ZilchBindFieldProperty(KeywordAndTypeCompletion);
  ZilchBindFieldProperty(AutoCompleteOnEnter);
  ZilchBindField(ColorScheme);
  ZilchBindFieldProperty(FontSize);

  type->AddAttribute(ObjectAttributes::cCore);
}

void TextEditorConfig::Serialize(Serializer& stream)
{
  // This has to be done since the original values were serialized as garbage
  // (didn't use SerializeNameDefault, and had no constructor / SetDefaults)
  // Therefore we had to tell it to serialize as another name, so we never pulled from the incorrectly saved data
  // Eventually when we roll a new config, these should be changed back to just SerializeNameDefault
  stream.SerializeFieldDefault("ShowWhiteSpace2", ShowWhiteSpace, true);
  stream.SerializeFieldDefault("ConfidentAutoCompleteOnSymbols6", ConfidentAutoCompleteOnSymbols, true);
  stream.SerializeFieldDefault("LocalWordCompletion", LocalWordCompletion, true);
  stream.SerializeFieldDefault("KeywordAndTypeCompletion", KeywordAndTypeCompletion, true);
  stream.SerializeFieldDefault("AutoCompleteOnEnter6", AutoCompleteOnEnter, true);
  SerializeNameDefault(FontSize, uint(13));
  SerializeNameDefault(ColorScheme, String("DarkZero"));
  SerializeNameDefault(LineNumbers, true);
  SerializeNameDefault(CodeFolding, false);
  SerializeNameDefault(TextMatchHighlighting, true);
  SerializeNameDefault(HighlightPartialTextMatch, false);
  SerializeEnumNameDefault(TabWidth, TabWidth, TabWidth::TwoSpaces);
}

//-------------------------------------------------------------- Recent Projects
uint RecentProjects::mAbsoluteMaxRecentProjects = 50;

//******************************************************************************
ZilchDefineType(RecentProjects, builder, type)
{
  ZeroBindComponent();
  ZeroBindSetup(SetupMode::DefaultSerialization);
}

//******************************************************************************
void RecentProjects::Serialize(Serializer& stream)
{
  SerializeNameDefault(mMaxRecentProjects, 20u);
  SerializeNameDefault(mRecentProjects, mRecentProjects);
}

//******************************************************************************
void RecentProjects::Initialize(CogInitializer& initializer)
{
  RemoveMissingProjects();
}

//******************************************************************************
void RecentProjects::AddRecentProject(StringParam file, bool sendsEvent)
{
  // See if we can make room for this project if needed
  RemoveMissingProjects();

  // If we already contain the file being added then don't remove or add anything
  if(mRecentProjects.Contains(file) == false)
  {
    // If we've hit the limit of recent projects, remove the oldest project
    if(mRecentProjects.Size() >= mAbsoluteMaxRecentProjects)
      RemoveRecentProject(GetOldestProject());

    mRecentProjects.Insert(file);
  }

  if(sendsEvent)
  {
    Event toSend;
    DispatchEvent(Events::RecentProjectsUpdated, &toSend);
  }
}

//******************************************************************************
void RecentProjects::RemoveRecentProject(StringParam projectFile, bool sendsEvent)
{
  mRecentProjects.Erase(projectFile);

  if(sendsEvent)
  {
    Event toSend;
    DispatchEvent(Events::RecentProjectsUpdated, &toSend);
  }
}

//******************************************************************************
class FileTimeSorter
{
public:
  bool operator()(StringParam left, StringParam right)
  {
    return CheckFileTime(left, right) == 1;
  }
};

//******************************************************************************
void RecentProjects::GetProjectsByDate(Array<String>& projects)
{
  // Make sure to remove all missing projects first
  RemoveMissingProjects();

  projects.Reserve(mRecentProjects.Size());

  forRange(String location, mRecentProjects.All())
  {
    projects.PushBack(location);
  }

  // Sort the projects on when they were last opened.
  Sort(projects.All(), FileTimeSorter());
  // Only give them that max number of projects they request
  if(projects.Size() > mMaxRecentProjects)
    projects.Resize(mMaxRecentProjects);
}

//******************************************************************************
void RecentProjects::CopyProjects(RecentProjects* source)
{
  mRecentProjects = source->mRecentProjects;
  mMaxRecentProjects = source->mMaxRecentProjects;
  RemoveMissingProjects();
}

//******************************************************************************
size_t RecentProjects::GetRecentProjectsCount() const
{
  return mRecentProjects.Size();
}

//******************************************************************************
String RecentProjects::GetOldestProject()
{
  String oldestProject;
  TimeType time = cTimeMax;
  forRange(String currProjectPath, mRecentProjects.All())
  {
    TimeType currTime = 0;
    
    // Missing projects are considered old
    if(FileExists(currProjectPath))
      currTime = GetFileModifiedTime(currProjectPath);

    if(currTime < time)
    {
      time = currTime;
      oldestProject = currProjectPath;
    }
  }

  return oldestProject;
}

//******************************************************************************
void RecentProjects::UpdateMaxNumberOfProjects(uint maxRecentProjects, bool sendsEvent)
{
  mMaxRecentProjects = maxRecentProjects;

  // See if we can make room
  RemoveMissingProjects();

  // Remove all older projects until we reach the limit
  while(mRecentProjects.Size() > mAbsoluteMaxRecentProjects)
    RemoveRecentProject(GetOldestProject());

  if(sendsEvent)
  {
    Event toSend;
    DispatchEvent(Events::RecentProjectsUpdated, &toSend);
  }
}

//******************************************************************************
void RecentProjects::RemoveMissingProjects()
{
  HashSet<String> recentProjects(mRecentProjects);
  mRecentProjects.Clear();

  forRange(String project, recentProjects.All())
  {
    if(FileExists(project))
      mRecentProjects.Insert(project);
  }
}

//------------------------------------------------------------------- Build Info
ZilchDefineType(BuildInfo, builder, type)
{
  ZeroBindComponent();
}

void BuildInfo::Serialize(Serializer& stream)
{
  SerializeName(ProjectName);
  SerializeName(Source);
  SerializeName(Output);
}

cstr cConfigFileName = "ConfigurationV6.data";

String GetConfigFile(StringParam applicationName)
{
  return FilePath::Combine(GetUserDocumentsDirectory(), applicationName, cConfigFileName);
}

void SaveConfig(Cog* configCog)
{
  if (!MainConfig::sConfigCanSave)
    return;

  MainConfig* config = configCog->has(MainConfig);
  String applicationName = config->ApplicationName;
  String fileName = GetConfigFile(applicationName);
  String configDirectory = FilePath::Combine(GetUserDocumentsDirectory(), applicationName);
  CreateDirectoryAndParents(configDirectory);
  String configFile = FilePath::Combine(configDirectory, cConfigFileName);

  ObjectSaver saver;
  Status status;
  saver.Open(status, configFile.c_str());
  ErrorIf(status.Failed(), "Failed to save config file");
  saver.SaveInstance(configCog);

  //SaveToDataFile(*configCog, configFile);
}

void RemoveConfig(Cog* config)
{
  MainConfig* mainConfig = config->has(MainConfig);
  String configFile = GetConfigFile(mainConfig->ApplicationName);
  DeleteFile(configFile);
}

Cog* LoadConfig(StringParam applicationName, bool useDefault, ZeroStartupSettings& settings)
{
  ZPrint("Build Version: %s\n", GetBuildVersionName());

  ZPrint("Loading configuration for %s...\n", applicationName.c_str());

  static const String cDataDirectoryName("Data");
  static const String cDefaultConfigFile("Configuration.data");

  //Get Paths
  String appCacheDirectory = GetUserLocalDirectory();
  String documentDirectory = GetUserDocumentsDirectory();
  String applicationDirectory = GetApplicationDirectory();
  String configFile = GetConfigFile(applicationName);

  Cog* configCog = nullptr;
  bool userConfigExists = false;

  // Locations to look for the config file.
  // Some of them are absolute, some are relative to the working directory.
  String searchConfigPaths[] =
  {
    // The user config.
    configFile,
    // In the application directory.
    FilePath::Combine(applicationDirectory, cDefaultConfigFile),
    // In the working directory.
    cDefaultConfigFile,
    // Into the application/Data directory.
    FilePath::Combine(applicationDirectory, cDataDirectoryName, cDefaultConfigFile),
    // Into the working/Data directory.
    FilePath::Combine(cDataDirectoryName, cDefaultConfigFile),
  };

  const size_t searchconfigPathsCount = sizeof(searchConfigPaths) / sizeof(*searchConfigPaths);
  for (size_t i = 0; i < searchconfigPathsCount; ++i)
  {
    // Skip the user config if we're only going to use a default config.
    if (useDefault && i == 0)
      continue;

    StringParam path = searchConfigPaths[i];
    if (FileExists(path))
    {
      configCog = Z::gFactory->Create(Z::gEngine->GetEngineSpace(), path, 0, nullptr);

      // Make sure we successfully created the config Cog from the data file.
      if (configCog != nullptr)
      {
        userConfigExists = (i == 0);
        ZPrintFilter(Filter::DefaultFilter, "Using config '%s'.\n", path.c_str());
        break;
      }
    }
  }

  if(configCog == nullptr)
  {
    String msg = BuildString("Failed to find or open the configuration file, '", cConfigFileName,
      "', in the working directory or application directory");
    FatalEngineError(msg.c_str());

    return nullptr;
  }

  HasOrAdd<EditorSettings>(configCog);
  MainConfig* mainConfig = configCog->has(MainConfig);
  mainConfig->ApplicationName = applicationName;
  mainConfig->mConfigDidNotExist = !userConfigExists;
  mainConfig->DataDirectory = cDataDirectoryName;
  //mainConfig->SourceDirectory = sourceDirectory;
  mainConfig->ApplicationDirectory = applicationDirectory;

  //Build info is generated by the build process and if present the
  //engine was built locally.
  BuildInfo buildInfo;
  Array<String> buildInfoSearchPaths;
  buildInfoSearchPaths.PushBack(FilePath::Combine(applicationDirectory, "BuildInfo.data"));
  buildInfoSearchPaths.PushBack(FilePath::Combine(GetWorkingDirectory(), "BuildInfo.data"));
  for(size_t i = 0; i < buildInfoSearchPaths.Size(); ++i)
  {
    String buildInfoFile = buildInfoSearchPaths[i];
    bool buildInfoExists = FileExists(buildInfoFile);
    if(buildInfoExists)
    {
      //Engine was built locally so pull data from the source location
      LoadFromDataFile(buildInfo, buildInfoFile);

      mainConfig->SourceDirectory = buildInfo.Source;
      mainConfig->DataDirectory = FilePath::Combine(buildInfo.Source, cDataDirectoryName);
      mainConfig->mLocallyBuilt = true;
      break;
    }
  }
  
  if (settings.mEmbeddedPackage)
  {
    mainConfig->DataDirectory = FilePath::Combine(settings.mEmbeddedWorkingDirectory, cDataDirectoryName);
  }

  if(!userConfigExists)
  {
    //Set the application name this allows different native programs
    //to have different config files.
    mainConfig->ApplicationName = applicationName;
    SaveConfig(configCog);
  }

  configCog->mFlags.SetFlag(CogFlags::Protected);
  return configCog;
}

}//namespace Zero
