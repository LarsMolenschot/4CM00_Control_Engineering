function [fig, H_tile, Coh_tile] = PlotProcessedData(data,title)
    w = size(data);    
    l = 0;
    for i = 1:w(2)
        %data exists of struct{processedData, tf_to_plot}
        tf_to_plot = cell2mat(data(2,i));
        cell_data = cell2mat(data(1,i));
    
    
        % Show available fields
        % disp('Available fields in data:');
        % disp(fields(cell_data))
    
        % Check if requested field exists
        if ~isfield(cell_data, tf_to_plot)
            error('Field "%s" not found in data.', tf_to_plot);
        end


        l = max(l, length(cell_data.f));
        l = max(l, length(cell_data.(tf_to_plot)));
        l = max(l, length(cell_data.Coh));
    end


    %build data vectors
    F = zeros(l,w(2));
    tf_data = zeros(l,w(2));
    c_w = 0;
    for i = 1:w(2)
        cell_data = cell2mat(data(1,i));
        size_Coh = size(cell_data.Coh);
        c_w = c_w + size_Coh(2);
    end
    Coh = zeros(l,c_w);
    j = 0;
    for i = 1 : w(2)
        tf_to_plot = cell2mat(data(2,i));
        cell_data = cell2mat(data(1,i));

        F(1:length(cell_data.f),i) = cell_data.f;
        tf_data(1:length(cell_data.(tf_to_plot)),i) = cell_data.(tf_to_plot);
        size_Coh = size(cell_data.Coh);
       for k = 1 : size_Coh(2)
            j = j+1;
            Coh(1:length(cell_data.Coh(:,k)),j) = cell_data.Coh(:,k);
        end
    end

   [fig, H_tile, Coh_tile] = mybode(F,tf_data,Coh,title);

end