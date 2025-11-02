function [processedData]= GetProcessedData(Path, processedType, MeasurementNumber)
    folder = Path + "/processed_signals/" + processedType + "/MeasurementOrder";
    found = GetData(MeasurementNumber,folder);
    
    if(isempty(found))
        processedData = [];
        return;
    end
    processedData = found.Data.calculatedData;
end