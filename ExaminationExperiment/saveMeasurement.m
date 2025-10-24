function Data = saveMeasurement(settings, signals, calculatedData, relativePath)
Data.settings = settings;
Data.signals = signals;
Data.calculatedData = calculatedData;

[Path,fileName,~] = fileparts(relativePath);
parts = strsplit(Path, filesep);


%go to folder -> create path if it does not exist yet
% Build folder hierarchy step by step
current = "";
for i = 1:numel(parts)
    current = fullfile(current, parts{i});
    if ~isfolder(current)
        mkdir(current);
    end
end

PathRaw = Path + "/Raw/";
PathNumberd = Path + "/MeasurementOrder/";
if ~isfolder(PathRaw)
        mkdir(PathRaw);
end
if ~isfolder(PathNumberd)
    mkdir(PathNumberd);
end

IndexPath = Path+"/MeasurementIndex.mat";
storeIndex = 1;
if isfile(IndexPath)
    read = load(IndexPath);
    storeIndex = read.storeIndex;
else %create file
    save(IndexPath,"storeIndex");
end



%always save raw data with timestamp
nowTime = now;  % current time
timeMark = datestr(nowTime,'ddd_dd_mmm_HH') + "u" + ...
           datestr(nowTime,'MM') + "m" + ...
           datestr(nowTime,'SS') + "s";

StoreName =  fileName + "_" + timeMark;
Data.FileName = StoreName;
Data.index = storeIndex;
save(PathRaw + StoreName,"Data");

%save the numbered data
save(PathNumberd +"/"+ storeIndex +"_"+ fileName,"Data");
storeIndex = storeIndex +1;
save(IndexPath,"storeIndex");

end