function [fig, H_tile, Coh_tile] = mybode(f,H,C,fig_title)
    fig = figure;
    t = tiledlayout(3,1,"TileSpacing","tight");
    title(t,'Bode: ' + fig_title);
    
    size_h = size(H);
    size_f = size(f);
    if(size_f(2) == 1) %copy the freq to use for all plots
        f_copy = f;
        f = zeros(size(H));
        for i = 1 : size_h(2)
            f(:,i) = f_copy;
        end
    end

    %Magnitude
    H_tile = nexttile;
    %plot(f,20*log10(abs(H)));
    for i = 1 : size_h(2)
        plot(f(:,i),20*log10(abs(H(:,i)))); hold on;
    end
    xscale log; grid on;
    %xlabel('Frequency [Hz]');
    ylabel('|H| [dB]');
    title('Magnitude');
    %legend set at magnitude plot
    legend(arrayfun(@(i) sprintf('H_%d',i),1:size_h(2),'UniformOutput',false));
    
    %Phase
    nexttile;
    
    for i = 1 : size_h(2)
        plot(f(:,i),rad2deg(angle(H(:,i)))); hold on;    
    end
    xscale log; grid on;
    %xlabel('Frequency [Hz]');
    ylabel('Phase [deg]');
    title('Phase');
    %legend(arrayfun(@(i) sprintf('H_%d',i),1:size_h(2),'UniformOutput',false));

    if(~size(C))
        xlabel('Frequency [Hz]');
        Coh_tile = 0;
        return;
    end
    
    %Coherance
    Coh_tile = nexttile;
    size_c = size(C);
    for i = 1 : size_c(2)
        semilogx(f(:,i),C(:,i)); hold on;
    end
    grid on;
    title('Coherence');
    xlabel('Frequency [Hz]');
    legend(arrayfun(@(i) sprintf('Coh %d',i),1:size_c(2),'UniformOutput',false));
end