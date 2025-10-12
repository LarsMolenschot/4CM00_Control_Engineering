function [fig, H_tile, Coh_tile] = PlotProcessedData(data,title)
    w = length(data);    
    l = 0;
    for i = 1:w
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
        l = max(l, length(cell_data.C));
    end


    %build data vectors
    F = zeros(l,w);
    tf_data = zeros(l,w);
    c_w = 0;
    for i = 1:w
        cell_data = cell2mat(data(1,i));
        size_C = size(cell_data.C);
        c_w = c_w + size_C(2);
    end
    C = zeros(l,c_w);
    j = 0;
    for i = 1 : length(data)
        tf_to_plot = cell2mat(data(2,i));
        cell_data = cell2mat(data(1,i));

        F(1:length(cell_data.f),i) = cell_data.f;
        tf_data(1:length(cell_data.(tf_to_plot)),i) = cell_data.(tf_to_plot);
        size_C = size(cell_data.C);
       for k = 1 : size_C(2)
            j = j+1;
            C(1:length(cell_data.C(:,k)),j) = cell_data.C(:,k);
        end
    end

   [fig, H_tile, Coh_tile] = mybode(F,tf_data,C,title);

end