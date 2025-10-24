function foundData = GetMyData(Number,Folder)
    files = dir(fullfile(Folder, '*_*'));  % only files with underscore
    files = files(~[files.isdir]);          % remove any folders
    
    filePath = "";
    for k = 1:length(files)
        nameParts = split(files(k).name, '_'); 
        if str2double(nameParts{1}) == Number
            filePath = fullfile(Folder, files(k).name);  % full path to the file
            break;  % exit loop once found
        end
    end

    if(filePath == "")
        warning("File #" + Number + " not found!");
        foundData = [];
        return;
    end
    foundData = load(filePath);
end