function [d,y,u,e,r] = StartFRFMeasurement(p,N_samples,variance, ModelName)
    % Check if the model is running, makes no sense to measure otherwise.
    if ~strcmp(get_param(ModelName,'SimulationStatus'),'external')
       error('The model is not running, can not perform a measurement.');
       return
    end

    BlockPaths = find_system(ModelName);    
    Index_noise = find(contains(BlockPaths,'Noise')); % Get the correct string
    
    % If we have more than 1 index, this means duplicate blocks, should not
    % happen! Give a warning, and then try to trigger the first.
    if length(Index_noise) > 1
        warning('There appear to be duplicate noise blocks in your model. Please remove all duplicate blocks.');
        Index_noise = Index_noise(1);
    end
    
    fprintf(['Starting measurement with white noise on the disturbance.\n',...
        'If you are planning on doing an FRF measurement, \n',...
        'think carefully about the signals you need and consider open/closed loop.\n']);
    
    % Set the variance of the noise to 0.1
    set_param(BlockPaths{Index_noise},'variance',variance);
    pause(0.1);
    
    % Do the measurement
    % How many signals do you need to record?
    N_signals = 5;
    measurement = SPERTE_Measure_And_Collect(p,N_signals,N_samples,ModelName);
    pause(0.1);
    
    % Turn of the noise
    set_param(BlockPaths{Index_noise},'variance','0')
    pause(0.1);
    
    %measured signals
    d = measurement(:,1);
    y = measurement(:,2);
    u = measurement(:,3);
    e = measurement(:,4);
    r = measurement(:,5);
end
