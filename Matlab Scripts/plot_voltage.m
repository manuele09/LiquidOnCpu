function plot_voltage(log_file, x, y)
    % Read the log file
    data = readtable(log_file);

    % Get the unique steps
    steps = unique(data.Step);

    % Number of neurons to plot
    num_neurons = x * y;

    % Create a subplot for each neuron ID
    sub_plot_pos = 1;
    for i = 1:num_neurons
        neuron_id = i-1;

        % Extract neuron data for the current neuron ID
        neuron_data = data(data.Id == neuron_id, :);


        % Create a subplot for membrane potential 
        subplot(x, y, sub_plot_pos);
        plot(steps, neuron_data.V);
        title(sprintf('Neuron %d', neuron_id));
        xlabel('Step');
        ylabel('Potential (mV)');
        sub_plot_pos = sub_plot_pos + 1;

    
    end
end
