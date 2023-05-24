function plot_neuron_data(log_file, neuron_ids, plot_type)
    % Read the log file
    data = readtable(log_file);

    % Get the unique steps
    steps = unique(data.Step);

    % Number of neurons to plot
    num_neurons = length(neuron_ids);

    % If plot_type is not specified, default to plotting both potential and current
    if nargin < 3
        plot_type = 'both';
    end

    % Determine the number of columns in the subplot based on the plot_type
    if strcmp(plot_type, 'both')
        num_columns = 2;
    else
        num_columns = 1;
    end

    % Create a subplot for each neuron ID
    sub_plot_pos = 1;
    for i = 1:num_neurons
        neuron_id = neuron_ids(i);

        % Extract neuron data for the current neuron ID
        neuron_data = data(data.Id == neuron_id, :);

        if strcmp(plot_type, 'p') || strcmp(plot_type, 'both')
            % Create a subplot for membrane potential
            subplot(num_neurons, num_columns, sub_plot_pos);
            plot(steps, neuron_data.V);
            title(sprintf('Neuron %d - Membrane Potential', neuron_id));
            xlabel('Step');
            ylabel('Potential (mV)');
            sub_plot_pos = sub_plot_pos + 1;
        end

        if strcmp(plot_type, 'c') || strcmp(plot_type, 'both')
            % Create a subplot for input current
            subplot(num_neurons, num_columns, sub_plot_pos);
            plot(steps, neuron_data.I);
            title(sprintf('Neuron %d - Input Current', neuron_id));
            xlabel('Step');
            ylabel('Current (pA)');
            sub_plot_pos = sub_plot_pos + 1;
        end
    end
end
