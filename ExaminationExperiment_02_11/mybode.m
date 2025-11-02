function fig_handling = mybode(f, H, C, fig_title, fig_handling)
    % Adaptive Bode: grows/shrinks the tiledlayout based on presence of C

    hasCoh = ~isempty(C) && size(C,2) > 0;
    needRows = 2 + double(hasCoh);

    %=== Create or adapt figure/layout ===%
    if nargin < 5 || ~isstruct(fig_handling) || ~isfield(fig_handling,'fig') || ~isvalid(fig_handling.fig)
        fig_handling.fig = figure('Name', "Bode: " + fig_title);
        fig_handling = buildLayout(fig_handling, needRows, fig_title);
    else
        figure(fig_handling.fig);
        % If layout row count differs, rebuild inside same figure
        if ~isfield(fig_handling,'t') || ~isvalid(fig_handling.t) || fig_handling.t.GridSize(1) ~= needRows
            clf(fig_handling.fig); % clear but keep same figure handle
            fig_handling = buildLayout(fig_handling, needRows, fig_title);
        end
    end

    %=== Frequency matrices per group (avoid mismatches) ===%
    % For H plots
    if isempty(H), H = zeros(0,0); end
    if size(f,2)==1 && ~isempty(H)
        fH = repmat(f,1,size(H,2));
    else
        fH = f;
        if ~isempty(H) && size(fH,2)~=size(H,2)
            error('f columns must match H columns (or pass f as a single column).');
        end
    end

    % For C plots
    if hasCoh
        if size(f,2)==1
            fC = repmat(f,1,size(C,2));
        else
            fC = f;
            if size(fC,2)~=size(C,2)
                error('f columns must match C columns (or pass f as a single column).');
            end
        end
    end

    %=== Magnitude ===%
    axH = fig_handling.H_tile;  hold(axH,'on');
    if ~isempty(H)
        fig_handling.H_plot = gobjects(1,size(H,2));
        for i=1:size(H,2)
            fig_handling.H_plot(i) = plot(axH, fH(:,i), 20*log10(abs(H(:,i))));
        end
    end
    set(axH,'XScale','log'); grid(axH,'on');
    ylabel(axH,'|H| [dB]','FontSize',24);
    title(axH,'Magnitude','FontSize',24);

    %=== Phase ===%
    axP = fig_handling.P_tile;  hold(axP,'on');
    if ~isempty(H)
        fig_handling.P_plot = gobjects(1,size(H,2));
        for i=1:size(H,2)
            fig_handling.P_plot(i) = plot(axP, fH(:,i), rad2deg(angle(H(:,i))));
        end
    end
    set(axP,'XScale','log'); grid(axP,'on');
    ylabel(axP,'Phase [deg]','FontSize',24);
    title(axP,'Phase','FontSize',24);

    %=== Coherence (only when present) ===%
    if hasCoh
        axC = fig_handling.Coh_tile; hold(axC,'on');
        fig_handling.C_plot = gobjects(1,size(C,2));
        for i=1:size(C,2)
            fig_handling.C_plot(i) = plot(axC, fC(:,i), C(:,i));
        end
        set(axC,'XScale','log'); grid(axC,'on');
        ylim(axC,[0 1]);
        xlabel(axC,'Frequency [Hz]','FontSize',24);
        ylabel(axC,'Coherence [-]','FontSize',24);
        title(axC,'Coherence','FontSize',24);
    else
        % Put the xlabel on the last visible tile when no coherence
        xlabel(axP,'Frequency [Hz]','FontSize',24);
    end
end

function fig_handling = buildLayout(fig_handling, rows, fig_title)
    % Helper: (re)build a 2- or 3-row layout and tiles
    fig_handling.t = tiledlayout(fig_handling.fig, rows, 1, "TileSpacing","tight");
    title(fig_handling.t, 'Bode: ' + fig_title,'FontSize',24);

    fig_handling.H_tile = nexttile(fig_handling.t,1);
    fig_handling.P_tile = nexttile(fig_handling.t,2);

    if rows==3
        fig_handling.Coh_tile = nexttile(fig_handling.t,3);
    else
        fig_handling.Coh_tile = [];
    end
end
