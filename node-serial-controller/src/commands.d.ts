import * as $protobuf from "protobufjs";

/** Relay enum. */
export enum Relay {
    ALL = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
}

/** Properties of a StatusResponse. */
export interface IStatusResponse {

    /** StatusResponse relayOne */
    relayOne: StatusResponse.IStatus;

    /** StatusResponse relayTwo */
    relayTwo: StatusResponse.IStatus;

    /** StatusResponse relayThree */
    relayThree: StatusResponse.IStatus;

    /** StatusResponse relayFour */
    relayFour: StatusResponse.IStatus;
}

/** Represents a StatusResponse. */
export class StatusResponse implements IStatusResponse {

    /**
     * Constructs a new StatusResponse.
     * @param [properties] Properties to set
     */
    constructor(properties?: IStatusResponse);

    /** StatusResponse relayOne. */
    public relayOne: StatusResponse.IStatus;

    /** StatusResponse relayTwo. */
    public relayTwo: StatusResponse.IStatus;

    /** StatusResponse relayThree. */
    public relayThree: StatusResponse.IStatus;

    /** StatusResponse relayFour. */
    public relayFour: StatusResponse.IStatus;

    /**
     * Creates a new StatusResponse instance using the specified properties.
     * @param [properties] Properties to set
     * @returns StatusResponse instance
     */
    public static create(properties?: IStatusResponse): StatusResponse;

    /**
     * Encodes the specified StatusResponse message. Does not implicitly {@link StatusResponse.verify|verify} messages.
     * @param message StatusResponse message or plain object to encode
     * @param [writer] Writer to encode to
     * @returns Writer
     */
    public static encode(message: IStatusResponse, writer?: $protobuf.Writer): $protobuf.Writer;

    /**
     * Encodes the specified StatusResponse message, length delimited. Does not implicitly {@link StatusResponse.verify|verify} messages.
     * @param message StatusResponse message or plain object to encode
     * @param [writer] Writer to encode to
     * @returns Writer
     */
    public static encodeDelimited(message: IStatusResponse, writer?: $protobuf.Writer): $protobuf.Writer;

    /**
     * Decodes a StatusResponse message from the specified reader or buffer.
     * @param reader Reader or buffer to decode from
     * @param [length] Message length if known beforehand
     * @returns StatusResponse
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    public static decode(reader: ($protobuf.Reader|Uint8Array), length?: number): StatusResponse;

    /**
     * Decodes a StatusResponse message from the specified reader or buffer, length delimited.
     * @param reader Reader or buffer to decode from
     * @returns StatusResponse
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    public static decodeDelimited(reader: ($protobuf.Reader|Uint8Array)): StatusResponse;

    /**
     * Verifies a StatusResponse message.
     * @param message Plain object to verify
     * @returns `null` if valid, otherwise the reason why it is not
     */
    public static verify(message: { [k: string]: any }): (string|null);

    /**
     * Creates a StatusResponse message from a plain object. Also converts values to their respective internal types.
     * @param object Plain object
     * @returns StatusResponse
     */
    public static fromObject(object: { [k: string]: any }): StatusResponse;

    /**
     * Creates a plain object from a StatusResponse message. Also converts values to other types if specified.
     * @param message StatusResponse
     * @param [options] Conversion options
     * @returns Plain object
     */
    public static toObject(message: StatusResponse, options?: $protobuf.IConversionOptions): { [k: string]: any };

    /**
     * Converts this StatusResponse to JSON.
     * @returns JSON object
     */
    public toJSON(): { [k: string]: any };
}

export namespace StatusResponse {

    /** State enum. */
    enum State {
        OFF = 0,
        ON = 1
    }

    /** Properties of a Status. */
    interface IStatus {

        /** Status relay */
        relay: Relay;

        /** Status state */
        state: StatusResponse.State;
    }

    /** Represents a Status. */
    class Status implements IStatus {

        /**
         * Constructs a new Status.
         * @param [properties] Properties to set
         */
        constructor(properties?: StatusResponse.IStatus);

        /** Status relay. */
        public relay: Relay;

        /** Status state. */
        public state: StatusResponse.State;

        /**
         * Creates a new Status instance using the specified properties.
         * @param [properties] Properties to set
         * @returns Status instance
         */
        public static create(properties?: StatusResponse.IStatus): StatusResponse.Status;

        /**
         * Encodes the specified Status message. Does not implicitly {@link StatusResponse.Status.verify|verify} messages.
         * @param message Status message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: StatusResponse.IStatus, writer?: $protobuf.Writer): $protobuf.Writer;

        /**
         * Encodes the specified Status message, length delimited. Does not implicitly {@link StatusResponse.Status.verify|verify} messages.
         * @param message Status message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: StatusResponse.IStatus, writer?: $protobuf.Writer): $protobuf.Writer;

        /**
         * Decodes a Status message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns Status
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: ($protobuf.Reader|Uint8Array), length?: number): StatusResponse.Status;

        /**
         * Decodes a Status message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns Status
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: ($protobuf.Reader|Uint8Array)): StatusResponse.Status;

        /**
         * Verifies a Status message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a Status message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns Status
         */
        public static fromObject(object: { [k: string]: any }): StatusResponse.Status;

        /**
         * Creates a plain object from a Status message. Also converts values to other types if specified.
         * @param message Status
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: StatusResponse.Status, options?: $protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this Status to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }
}

/** Properties of a CommandRequest. */
export interface ICommandRequest {

    /** CommandRequest command */
    command: CommandRequest.Command;

    /** CommandRequest relay */
    relay?: (Relay|null);

    /** CommandRequest iterations */
    iterations?: (number|null);

    /** CommandRequest onMillis */
    onMillis?: (number|null);

    /** CommandRequest offMillis */
    offMillis?: (number|null);

    /** CommandRequest pauseMillis */
    pauseMillis?: (number|null);
}

/** Represents a CommandRequest. */
export class CommandRequest implements ICommandRequest {

    /**
     * Constructs a new CommandRequest.
     * @param [properties] Properties to set
     */
    constructor(properties?: ICommandRequest);

    /** CommandRequest command. */
    public command: CommandRequest.Command;

    /** CommandRequest relay. */
    public relay: Relay;

    /** CommandRequest iterations. */
    public iterations: number;

    /** CommandRequest onMillis. */
    public onMillis: number;

    /** CommandRequest offMillis. */
    public offMillis: number;

    /** CommandRequest pauseMillis. */
    public pauseMillis: number;

    /**
     * Creates a new CommandRequest instance using the specified properties.
     * @param [properties] Properties to set
     * @returns CommandRequest instance
     */
    public static create(properties?: ICommandRequest): CommandRequest;

    /**
     * Encodes the specified CommandRequest message. Does not implicitly {@link CommandRequest.verify|verify} messages.
     * @param message CommandRequest message or plain object to encode
     * @param [writer] Writer to encode to
     * @returns Writer
     */
    public static encode(message: ICommandRequest, writer?: $protobuf.Writer): $protobuf.Writer;

    /**
     * Encodes the specified CommandRequest message, length delimited. Does not implicitly {@link CommandRequest.verify|verify} messages.
     * @param message CommandRequest message or plain object to encode
     * @param [writer] Writer to encode to
     * @returns Writer
     */
    public static encodeDelimited(message: ICommandRequest, writer?: $protobuf.Writer): $protobuf.Writer;

    /**
     * Decodes a CommandRequest message from the specified reader or buffer.
     * @param reader Reader or buffer to decode from
     * @param [length] Message length if known beforehand
     * @returns CommandRequest
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    public static decode(reader: ($protobuf.Reader|Uint8Array), length?: number): CommandRequest;

    /**
     * Decodes a CommandRequest message from the specified reader or buffer, length delimited.
     * @param reader Reader or buffer to decode from
     * @returns CommandRequest
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    public static decodeDelimited(reader: ($protobuf.Reader|Uint8Array)): CommandRequest;

    /**
     * Verifies a CommandRequest message.
     * @param message Plain object to verify
     * @returns `null` if valid, otherwise the reason why it is not
     */
    public static verify(message: { [k: string]: any }): (string|null);

    /**
     * Creates a CommandRequest message from a plain object. Also converts values to their respective internal types.
     * @param object Plain object
     * @returns CommandRequest
     */
    public static fromObject(object: { [k: string]: any }): CommandRequest;

    /**
     * Creates a plain object from a CommandRequest message. Also converts values to other types if specified.
     * @param message CommandRequest
     * @param [options] Conversion options
     * @returns Plain object
     */
    public static toObject(message: CommandRequest, options?: $protobuf.IConversionOptions): { [k: string]: any };

    /**
     * Converts this CommandRequest to JSON.
     * @returns JSON object
     */
    public toJSON(): { [k: string]: any };
}

export namespace CommandRequest {

    /** Command enum. */
    enum Command {
        STATUS = 0,
        HELP = 1,
        ON = 2,
        OFF = 3,
        INVERT = 4,
        SEQUENCE = 5,
        FLASH = 6,
        DEMO = 7
    }
}
