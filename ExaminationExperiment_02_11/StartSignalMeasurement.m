function [success, s1,s2,s3] = StartSignalMeasurement(p,N_samples,T_terminate,ModelName)
    % Check if the model is running, makes no sense to measure otherwise.
    tic
    success = false;
    while ~success
        if strcmp(get_param(ModelName,'SimulationStatus'),'external')
            %wait for the model to run and start taking measurements
            success = true;
        end
        if strcmp(get_param(ModelName,'SimulationStatus'),'running')
            %wait for the model to run and start taking measurements
            success = true;
            disp("Simulation is running, found in " + toc + " seconds, return without hardware measurements");
            return;
        end
        if toc >= T_terminate
            disp("No system online within " + toc + " seconds, return without hardware measurements");
            return;
        end
    end
    
    % Do the measurement
    % How many signals do you need to record?
    N_signals = 3;
    measurement = SPERTE_Measure_And_Collect(p,N_signals,N_samples,ModelName);
    pause(0.1);
    
    %measured signals
    s1 = measurement(:,1);
    s2 = measurement(:,2);
    s3 = measurement(:,3);
end
