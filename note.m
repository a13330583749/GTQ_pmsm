function obj=show(obj,app,x)
    dt = app.project_on.data2run_on.data2run_x.dt * 24;
    obj=fig_change(obj,app,7);
    app.CheckBox_5.Value = 1;
    app.CheckBox_6.Value = 1;
    app.CheckBox_7.Value = 1;
    switch x
        case  1 %展示一个示例
            cla(app.UIAxes_load);
            cla(app.UIAxes_X);
            cla(app.UIAxes_monay);
            y=app.project_on.data2run_on.data2run_x.load_ser;
            cla(app.UIAxes_load);
            plot(app.UIAxes_load,y);
            legend(app.UIAxes_load, '负荷数据');
            xlabel(app.UIAxes_load, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_load, 'kW·h');
            plot(app.UIAxes_X,app.project_on.simulation_on.result_sim.opt_E.x);
            legend(app.UIAxes_X, '充放电的策略向量');
            xlabel(app.UIAxes_X, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, '归一化后的充放电功率');
            plot(app.UIAxes_monay, app.project_on.simulation_on.result_sim.opt_E.E_stor(2:end));
            legend(app.UIAxes_monay, '电池容量');
            xlabel(app.UIAxes_monay, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_monay, "安时(Ah)")
        case 2
            cla(app.UIAxes_load);
            cla(app.UIAxes_X);
            cla(app.UIAxes_monay);
            plot(app.UIAxes_load,app.project_on.data2run_on.data2run_x.load_ser);
            legend(app.UIAxes_load, '负荷数据');
            xlabel(app.UIAxes_load, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_load, 'kW·h');
            plot(app.UIAxes_X,app.project_on.simulation_on.result_sim.opt_E.x);
            legend(app.UIAxes_X, '充放电的策略向量');
            xlabel(app.UIAxes_X, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, '归一化后的充放电功率');
            plot(app.UIAxes_monay, app.project_on.simulation_on.result_sim.opt_E.E_stor(2:end));
            legend(app.UIAxes_monay, '电池容量');
            xlabel(app.UIAxes_monay, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_monay, "安时(Ah)")
        case 3
            cla(app.UIAxes_load);
            cla(app.UIAxes_X);
            cla(app.UIAxes_monay);
            plot(app.UIAxes_load,app.project_on.data2run_on.data2run_x.load_ser);
            legend(app.UIAxes_load, '负荷数据');
            xlabel(app.UIAxes_load, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_load, 'kW·h');
            plot(app.UIAxes_X,app.project_on.simulation_on.result_sim.opt_E.p);
            legend(app.UIAxes_X, '充放电功率');
            xlabel(app.UIAxes_X, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, 'kW');
            plot(app.UIAxes_monay,app.project_on.simulation_on.result_sim.opt_E.estor(2:end));
            legend(app.UIAxes_monay, '电池容量');
            xlabel(app.UIAxes_monay, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_monay, "安时(Ah)")
        case 4
            cla(app.UIAxes_load);
            cla(app.UIAxes_X);
            cla(app.UIAxes_monay);
            plot(app.UIAxes_load,app.project_on.data2run_on.data2run_x.load_ser);
            legend(app.UIAxes_load, '负荷数据');
            xlabel(app.UIAxes_load, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_load, 'kW·h');
            plot(app.UIAxes_X,app.project_on.simulation_on.result_sim.opt_E.p);
            legend(app.UIAxes_X, '充放电功率');
            xlabel(app.UIAxes_X, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, 'kW');
            plot(app.UIAxes_monay,app.project_on.simulation_on.result_sim.opt_E.estor(2:end));
            legend(app.UIAxes_monay, '电池容量');
            xlabel(app.UIAxes_monay, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_monay, "安时(Ah)")
        case 10
            cla(app.UIAxes_load);
            cla(app.UIAxes_X);
            cla(app.UIAxes_monay);
            plot(app.UIAxes_load, app.project_on.data2run_on.data2run_x.AGC_P_ser);
            xlabel(app.UIAxes_load, "时间间隔："+num2str(dt) + "h");
            legend(app.UIAxes_load, 'AGC调频补偿费用');
            ylabel(app.UIAxes_load, '元');
            plot(app.UIAxes_X, app.project_on.simulation_on.result_sim.P)
            legend(app.UIAxes_X,'充放电状态')
            xlabel(app.UIAxes_X, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, 'kW');

            plot(app.UIAxes_monay, app.project_on.simulation_on.result_sim.opt_P_FM_d);
            hold(app.UIAxes_monay, 'on');
            plot(app.UIAxes_monay, app.project_on.simulation_on.result_sim.opt_P_FM_ch);
            legend(app.UIAxes_monay,'放电功率','充电功率')
            xlabel(app.UIAxes_monay, "时间间隔："+num2str(dt) + "h");
            ylabel(app.UIAxes_X, 'kW');
    end
    title(app.UIAxes_load, "图一");
    title(app.UIAxes_X, "图二");
    title(app.UIAxes_monay, "图三");
end