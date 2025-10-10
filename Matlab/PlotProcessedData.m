function [fig, H_tile, Coh_tile] = PlotProcessedData(data,title)
    w = length(data);    
    l = 0;
    for i = 1:w
        l = max(l, length(data(i).f));
        l = max(l, length(data(i).H));
        l = max(l, length(data(i).C));
    end


    %build data vectors
    F = zeros(l,w);
    H = zeros(l,w);
    c_w = 0;
    for i = 1:w
        size_C = size(data(i).C);
        c_w = c_w + size_C(2);
    end
    C = zeros(l,c_w);
    j = 0;
    for i = 1 : length(data)
        F(1:length(data(i).f),i) = data(i).f;
        H(1:length(data(i).H),i) = data(i).H;
        size_C = size(data(i).C);
       for k = 1 : size_C(2)
            j = j+1;
            C(1:length(data(i).C(:,k)),j) = data(i).C(:,k);
        end
    end

   [fig, H_tile, Coh_tile] = mybode(F,H,C,title);

end