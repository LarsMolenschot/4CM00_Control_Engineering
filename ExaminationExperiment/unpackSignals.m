function vars = unpackSignals(RawData, signalNames)
vars = struct();
for X = signalNames
    if(isfield(RawData.signals,X))
        vars.(X) = RawData.signals.(X);
    end
end
end