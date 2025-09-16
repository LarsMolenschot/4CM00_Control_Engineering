function [fig, legend_tile] = mybode(f,H,C,fig_title)
    fig = figure;
    t = tiledlayout(3,1,"TileSpacing","tight");
    title(t,'Bode: ' + fig_title);
    
    %Magnitude
    nexttile
    plot(f,20*log10(abs(H)));
    xscale log; grid on;
    %xlabel('Frequency [Hz]');
    ylabel('|H| [dB]');
    title('Magnitude');
    
    %Phase
    nexttile
    plot(f,rad2deg(unwrap(angle(H))));
    xscale log; grid on;
    %xlabel('Frequency [Hz]');
    ylabel('Phase [deg]');
    title('Phase');
    
    %Coherance
    legend_tile = nexttile;
    size_c = size(C);
    for i = 1 : size_c(2)
        semilogx(f,C(:,i)); hold on;
    end
    grid on;
    title('Coherence');
    xlabel('Frequency [Hz]');
    legend(arrayfun(@(i) sprintf('Coh %d',i),1:size_c(2),'UniformOutput',false));
end